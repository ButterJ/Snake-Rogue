#include "turn_based_entity.h"

#include <SDL3/SDL_log.h>

Turn_based_entity::Tick_result Turn_based_entity::tick()
{
    m_current_energy += m_energy_regeneration;

    if (m_current_energy >= m_turn_energy_cost)
    {
        m_current_energy -= m_turn_energy_cost;
        take_turn();
        return taking_turn;
    }

    return none;
}

void Turn_based_entity::die()
{
    On_death_callback();
}
