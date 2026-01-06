#include "time_system.h"
#include "i_player_entity.h"
#include <SDL3/SDL_log.h>

void Time_system::tick() // TODO: Fix problem that if two entities have their turn in the same tick the entity that entered the vector first does their turn first
{
    for (auto turn_based_entity : player_entities)
    {
        if (turn_based_entity.expired())
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Trying to tick an expired turn based entity");
            continue;
        }

        turn_based_entity.lock()->tick();
    }

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

    if (dynamic_cast<I_player_entity*>(turn_based_entity.lock().get()))
    {
        player_entities.push_back(turn_based_entity);
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
        player_entities.remove_if(lambda);
        return;
    }

    other_entities.remove_if(lambda); // TODO: Should benchmark if this is a performance hit
}
