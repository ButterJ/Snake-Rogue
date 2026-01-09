#include "game_controlled_creature.h"

void Game_controlled_creature::move(const Direction& direction)
{
    // TODO: Needs to be implemented, or in the child classes
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
