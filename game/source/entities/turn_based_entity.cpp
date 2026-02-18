#include "turn_based_entity.h"

#include "player_input_controller.h"

#include <SDL3/SDL_log.h>

Turn_based_entity::Turn_based_entity(std::shared_ptr<Input_controller> input_controller)
    : m_input_controller { input_controller }
{

    auto perform_input_action_lambda { [this](std::shared_ptr<Input_action> input_action)
                                       {
                                           Action_result action_result { perform_input_action(input_action) };

                                           if (action_result == Action_result::success)
                                           {
                                               on_turn_finished();
                                           }
                                       } };

    input_controller->On_action_decided.append(perform_input_action_lambda);
}

Turn_based_entity::Tick_result Turn_based_entity::tick()
{
    m_current_energy += m_energy_regeneration;

    if (m_current_energy >= m_turn_energy_cost)
    {
        m_current_energy -= m_turn_energy_cost;
        start_turn();
        return taking_turn;
    }

    return none;
}

bool Turn_based_entity::is_player_controlled() const
{
    auto casted { std::dynamic_pointer_cast<Player_input_controller>(m_input_controller) };

    if (casted)
    {
        return true;
    }

    return false;
}

void Turn_based_entity::try_processing_player_input()
{
    if (!is_player_controlled())
    {
        return;
    }

    auto player_input_controller { std::dynamic_pointer_cast<Player_input_controller>(m_input_controller) };
    player_input_controller->process_input();
}

void Turn_based_entity::start_turn()
{
    m_input_controller->start_deciding_on_action();
}

void Turn_based_entity::on_turn_finished()
{
    On_turn_finished_callback();
}

void Turn_based_entity::die()
{
    On_death_callback();
}
