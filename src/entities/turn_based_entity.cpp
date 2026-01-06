#include "turn_based_entity.h"
#include <SDL3/SDL_log.h>

void Turn_based_entity::tick()
{
    current_energy += energy_regeneration;

    if (current_energy >= turn_energy_cost)
    {
        current_energy -= turn_energy_cost;
        take_turn();
    }
}
