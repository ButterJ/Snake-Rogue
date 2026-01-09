#include "enemy.h"
#include <SDL3/SDL_log.h>

void Enemy::take_turn()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Monsters turn");
    body_parts.front().get()->move(Direction { 1, 0 });
}

void Enemy::set_position(const Position& position)
{
    if (body_parts.empty())
    {
        return;
    }

    // Set head position
    Body_part* head { body_parts.front().get() };
    head->get_transform_component().get()->position = position;

    if (body_parts.size() <= 1)
    {
        return;
    }

    // Set other body parts positions to the same as head
    for (auto i { ++body_parts.begin() }; i != body_parts.end(); i++)
    {
        i->get()->get_transform_component().get()->position = position;
    }
}
