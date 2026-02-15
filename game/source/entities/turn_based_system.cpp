#include "turn_based_system.h"

#include <SDL3/SDL_log.h>

#include <assert.h>

void Turn_based_system::update(float delta_time)
{
    if (!m_is_player_turn)
    {
        Turn_based_system::Process_result process_result { process_entity_turns() };

        if (process_result == Turn_based_system::Process_result::require_player_input)
        {
            m_is_player_turn = true;
        }
    }

    if (is_waiting_for_input_cooldown())
    {
        m_current_input_delay += delta_time;
        return;
    }

    if (m_is_player_turn)
    {
        assert(current_player_controlled_entity && "Trying to process input for an expired turn based entity");

        Player_controlled_entity::Input_result input_result { current_player_controlled_entity->process_input() };

        if (input_result == Player_controlled_entity::Input_result::turn_finished)
        {
            on_player_turn_finished();
        }
    }
}

const bool Turn_based_system::is_waiting_for_input_cooldown() const
{
    return m_current_input_delay < m_delay_after_input;
}

void Turn_based_system::on_player_turn_finished()
{
    m_is_player_turn = false;
    m_current_input_delay = 0.0f;
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

Turn_based_system::Process_result Turn_based_system::tick_player_controlled_entities()
{
    // Currently the time system is interrupted by players needing to input something. Without player entities the system will never be interrupted.
    // TODO: Consider making the time system not rely on player entities existing
    assert(player_controlled_entities.size() != 0 && "There are no player entities to process.");

    std::set<std::shared_ptr<Player_controlled_entity>> unprocessed_player_controlled_entities {};
    std::set_difference(player_controlled_entities.begin(), player_controlled_entities.end(), processed_player_controlled_entities.begin(), processed_player_controlled_entities.end(), std::inserter(unprocessed_player_controlled_entities, unprocessed_player_controlled_entities.begin()));

    for (const auto& player_controlled_entity : unprocessed_player_controlled_entities)
    {
        assert(player_controlled_entity && "Trying to tick an expired turn based entity");

        processed_player_controlled_entities.insert(player_controlled_entity);

        Turn_based_entity::Tick_result entity_tick_result { player_controlled_entity->tick() };

        if (entity_tick_result == Turn_based_entity::Tick_result::taking_turn)
        {
            current_player_controlled_entity = player_controlled_entity;
            return require_player_input;
        }
    }

    processed_player_controlled_entities.clear();

    return continue_processing;
}

void Turn_based_system::tick_other_entities()
{
    for (const auto& turn_based_entity : other_entities)
    {
        assert(turn_based_entity && "Trying to tick an expired turn based entity");

        turn_based_entity->tick();
    }
}

void Turn_based_system::register_entity(std::shared_ptr<Turn_based_entity> turn_based_entity)
{
    assert(turn_based_entity && "Trying to tick an expired turn based entity");

    auto on_death_lambda { [this, turn_based_entity]()
                           {
                               release_entity(turn_based_entity);
                           } };
    turn_based_entity->On_death_callback.append(on_death_lambda);

    std::shared_ptr<Player_controlled_entity> player_controlled_entity { std::dynamic_pointer_cast<Player_controlled_entity>(turn_based_entity) };

    if (player_controlled_entity)
    {
        player_controlled_entities.insert(player_controlled_entity);
        return;
    }

    other_entities.insert(turn_based_entity);
}

void Turn_based_system::release_entity(std::shared_ptr<Turn_based_entity> turn_based_entity)
{
    assert(turn_based_entity && "Trying to tick an expired turn based entity");

    auto derived { std::dynamic_pointer_cast<Player_controlled_entity>(turn_based_entity) };

    auto player_entity_iterator { player_controlled_entities.find(derived) };

    if (player_entity_iterator != player_controlled_entities.end())
    {
        player_controlled_entities.erase(player_entity_iterator);
        return;
    }

    auto other_entity_iterator { other_entities.find(turn_based_entity) };

    if (other_entity_iterator != other_entities.end())
    {
        other_entities.erase(other_entity_iterator);
        return;
    }
}
