#include "game_controlled_creature.h"

Action_result Game_controlled_creature::move(const Direction& direction)
{
    body_parts.front().get()->move(direction);
    return Action_result::success;
}

void Game_controlled_creature::add_body_part(std::shared_ptr<Body_part> body_part)
{
    body_parts.push_back(body_part);
}

void Game_controlled_creature::render()
{
    for (auto body_part : body_parts)
    {
        body_part.get()->render();
    }
}
