#include "enemy.h"

Action_result Enemy::move(const Direction& direction) // TODO: Return correct action result
{
    body_parts.front().get()->move(direction);
    return Action_result::success;
}

Action_result Enemy::set_position(const Position& position) // TODO: Return correct action result
{
    body_parts.front().get()->set_position(position);
    return Action_result::success;
}

Action_result Enemy::attack_adjacent_target(const std::vector<Body_part>& targets)
{
}

void Enemy::add_body_part(std::shared_ptr<Body_part> body_part)
{
    body_parts.push_back(body_part);
    body_part->On_death_callback.append([this]() // TODO: This is temporary where it is assumed that one body part dying means that the whole creature dies
                                        { on_death(); });
}

void Enemy::on_death()
{
    On_death_callback();
}

void Enemy::take_turn()
{
    std::vector<Body_part> adjacent_targets {};
    std::vector<Direction> occupied_directions {};
    move(Direction::Right);
}
