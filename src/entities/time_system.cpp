#include "time_system.h"
#include "i_player_entity.h"
#include <SDL3/SDL_log.h>
#include <assert.h>

const Time_system::Process_result Time_system::process_entity_turns()
{
    Process_result process_result { tick_player_controlled_entities() };

    if (process_result == require_player_input)
    {
        return process_result;
    }

    tick_other_entities();
}

Time_system::Process_result Time_system::tick_player_controlled_entities() // TODO: This function needs to be refactored (split up and unnecessary stuff removed)
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
            return require_player_input;
        }
    }

    for (auto player_controlled_entity : player_controlled_entities) // TODO: Maybe replace with forall?
    {
        player_controlled_entity.lock()->is_processed = false;
    }

    return continue_processing;
}

void Time_system::tick_other_entities()
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

void Time_system::register_entity(std::weak_ptr<Turn_based_entity> turn_based_entity)
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

void Time_system::release_entity(std::weak_ptr<Turn_based_entity> turn_based_entity)
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
