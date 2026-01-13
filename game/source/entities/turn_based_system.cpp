#include "turn_based_system.h"
#include "i_player_entity.h"
#include <SDL3/SDL_log.h>
#include <assert.h>

void Turn_based_system::update(float delta_time)
{
    if (!is_player_turn)
    {
        Turn_based_system::Process_result process_result { process_entity_turns() };

        if (process_result == Turn_based_system::Process_result::require_player_input)
        {
            is_player_turn = true;
        }
    }

    if (is_waiting_for_input_cooldown())
    {
        current_input_delay += delta_time;
        return;
    }

    if (is_player_turn)
    {
        assert(!current_player_controlled_entity.expired() && "Trying to process input for an expired turn based entity");

        Player_controlled_entity::Input_result input_result { current_player_controlled_entity.lock()->process_input() };

        if (input_result == Player_controlled_entity::Input_result::turn_finished) // TODO: Consider turning body into a function
        {
            is_player_turn = false;
            current_input_delay = 0.0f;
        }
    }
}

const bool Turn_based_system::is_waiting_for_input_cooldown() const
{
    return current_input_delay < delay_after_input;
}

const Turn_based_system::Process_result Turn_based_system::process_entity_turns()
{
    Process_result process_result { tick_player_controlled_entities() };

    if (process_result == require_player_input)
    {
        return process_result;
    }

    tick_other_entities();
    return continue_processing;
}

Turn_based_system::Process_result Turn_based_system::tick_player_controlled_entities() // TODO: This function needs to be refactored (split up and unnecessary stuff removed)
{
    if (player_controlled_entities.size() == 0) // Currently the time system is interrupted by players needing to input something. Without player entities the system will never be interrupted. // TODO: Consider making the time system not rely on player entities existing
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "There are no player entities to process.");
        throw;
    }

    for (auto player_controlled_entity : player_controlled_entities)
    {
        assert(!player_controlled_entity.expired() && "Trying to tick an expired turn based entity");

        auto locked_player_controlled_entity { player_controlled_entity.lock() };

        if (locked_player_controlled_entity->is_processed)
        {
            continue;
        }

        locked_player_controlled_entity->is_processed = true;
        Turn_based_entity::Tick_result entity_tick_result { locked_player_controlled_entity->tick() };

        if (entity_tick_result == Turn_based_entity::Tick_result::taking_turn)
        {
            current_player_controlled_entity = player_controlled_entity;
            return require_player_input;
        }
    }

    for (auto player_controlled_entity : player_controlled_entities) // TODO: Maybe replace with forall?
    {
        player_controlled_entity.lock()->is_processed = false;
    }

    return continue_processing;
}

void Turn_based_system::tick_other_entities()
{
    for (auto turn_based_entity : other_entities)
    {
        if (turn_based_entity.expired())
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Trying to tick an expired turn based entity");
            continue;
        }

        turn_based_entity.lock()->tick();
    }
}

void Turn_based_system::register_entity(std::weak_ptr<Turn_based_entity> turn_based_entity)
{
    if (turn_based_entity.expired())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Trying to register an expired turn based entity");
        return;
    }

    std::weak_ptr<Player_controlled_entity> player_controlled_entity { std::dynamic_pointer_cast<Player_controlled_entity>(turn_based_entity.lock()) };

    if (player_controlled_entity.lock())
    {
        player_controlled_entities.push_back(player_controlled_entity);
        return;
    }

    other_entities.push_back(turn_based_entity);
}

void Turn_based_system::release_entity(std::weak_ptr<Turn_based_entity> turn_based_entity)
{
    if (turn_based_entity.expired())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Trying to release an expired turn based entity");
        return;
    }

    auto entity_to_remove { turn_based_entity.lock() };

    auto lambda {
        [&entity_to_remove](const std::weak_ptr<Turn_based_entity>& entity_weak)
        {
            if (entity_weak.expired())
            {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Trying to iterate over an expired turn based entity");
                return false;
            }

            return entity_weak.lock().get() == entity_to_remove.get();
        }
    };

    if (dynamic_cast<I_player_entity*>(turn_based_entity.lock().get()))
    {
        player_controlled_entities.remove_if(lambda);
        return;
    }

    other_entities.remove_if(lambda); // TODO: Should benchmark if this is a performance hit
}
