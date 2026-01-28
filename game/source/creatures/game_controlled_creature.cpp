#include "game_controlled_creature.h"

Action_result Game_controlled_creature::move(const Direction& direction) // TODO: Return correct action result
{
    body_parts.front().get()->move(direction);
    return Action_result::success;
}

Action_result Game_controlled_creature::set_position(const Position& position) // TODO: Return correct action result
{
    body_parts.front().get()->set_position(position);
    return Action_result::success;
}

void Game_controlled_creature::add_body_part(std::shared_ptr<Body_part> body_part)
{
    body_parts.push_back(body_part);
    body_part->On_death_callback.append([this]() // TODO: This is temporary where it is assumed that one body part dying means that the whole creature dies
                                        { on_death(); });
}

void Game_controlled_creature::on_death()
{
    On_death_callback();
}
