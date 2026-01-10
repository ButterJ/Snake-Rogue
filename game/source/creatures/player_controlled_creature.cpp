#include "player_controlled_creature.h"

void Player_controlled_creature::add_body_part(std::shared_ptr<Body_part> body_part)
{
    body_parts.push_back(body_part);
}

void Player_controlled_creature::render()
{
    for (auto body_part : body_parts)
    {
        body_part.get()->render();
    }
}

void Player_controlled_creature::take_turn()
{
    // Player turns are driven by input in Turn_based_system::update
}
