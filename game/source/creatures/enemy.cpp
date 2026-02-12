#include "enemy.h"

#include "dungeon_layer.h"
#include "food.h"
#include "random_number_generator.h"

#include <SDL3/SDL_log.h>

#include <algorithm>

Action_result Enemy::move(const Direction& direction) // TODO: Return correct action result
{
    body_parts.front().get()->move(direction);
    m_last_position = get_head_position();
    return Action_result::success;
}

Action_result Enemy::set_position(const Position& position) // TODO: Return correct action result
{
    body_parts.front().get()->set_position(position);
    m_last_position = get_head_position();
    return Action_result::success;
}

void Enemy::on_body_part_death(std::shared_ptr<Body_part> body_part)
{
    die();
}

void Enemy::die() // TODO: Food spawn needs to be cleaned up
{
    Spritesheet food_spritesheet { "data/hashtag_01.png", 16.0f, 16.0f };
    Sprite_specification food_sprite_specification { food_spritesheet.get_sprite_specification(0, 0) };

    std::shared_ptr<Food> food_drop { std::make_shared<Food>(get_head_position(), food_sprite_specification, 50) };
    Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(get_head_position())->add_food(food_drop);

    Turn_based_entity::die();
}

void Enemy::take_turn()
{
    Creature::take_turn();

    // Basic enemy behaviour
    std::vector<std::shared_ptr<Body_part>> adjacent_targets {};
    std::vector<Direction> occupied_directions {};

    Position current_position { body_parts.front()->get_position() };

    for (auto direction : Direction::Orthogonal_directions)
    {
        auto current_floor { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor() };
        auto tile_to_check { current_floor->get_tile_at_position(current_position + direction) };

        if (!tile_to_check->is_occupied())
        {
            continue;
        }

        occupied_directions.push_back(direction);

        auto body_part_in_direction { tile_to_check->get_held_body_part() };
        if (!body_part_in_direction)
        {
            continue;
        }

        adjacent_targets.push_back(body_part_in_direction); // TODO: Differentiate between target and non target body parts
    }

    if (!adjacent_targets.empty())
    {
        attack_adjacent_target(adjacent_targets);
        return;
    }

    move_towards_weighted_random_direction(occupied_directions);
}

Action_result Enemy::attack_adjacent_target(const std::vector<std::shared_ptr<Body_part>>& targets)
{
    int random_body_part_index { Random_number_generator::get(0, targets.size() - 1) };
    std::shared_ptr<Body_part> body_part_to_attack { targets[random_body_part_index] };
    body_part_to_attack->change_health(-20); // TODO: Replace magic number

    return Action_result::success;
}

Action_result Enemy::move_towards_weighted_random_direction(const std::vector<Direction>& occupied_directions)
{
    auto current_floor { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor() };
    Position current_position { body_parts.front()->get_position() };

    std::vector<double> weights {};
    auto opposite_direction_from_last_move { m_last_move_direction.get_opposite_direction() };

    for (auto direction : Direction::Orthogonal_directions)
    {
        double direction_weight { 1.0 };

        auto it { std::ranges::find(occupied_directions, direction) };
        if (it != occupied_directions.end())
        {
            direction_weight = 0.0;
            weights.push_back(direction_weight);
            continue;
        }

        // Can't move into the opposite direction from the last move direction
        if (direction == opposite_direction_from_last_move)
        {
            direction_weight = 0.0;
            weights.push_back(direction_weight);
            continue;
        }

        // TODO: Maybe add so that walls are checked from further away
        auto tile_to_check { current_floor->get_tile_at_position(current_position + direction * 2.0) };
        if (tile_to_check->is_occupied())
        {
            direction_weight /= 4.0; // TODO: Remove magic number
        }
        else if (direction == m_last_move_direction)
        {
            direction_weight *= 15.0; // TODO: Remove magic number
        }

        weights.push_back(direction_weight);
    }

    if (std::all_of(weights.begin(), weights.end(), [](double weight)
                    { return weight == 0.0; }))
    {
        m_last_move_direction = Direction::Zero;
        return Action_result::failure;
    }

    int random_direction_index { std::discrete_distribution<int> { weights[0], weights[1], weights[2], weights[3] }(Random_number_generator::mersenne_twister) };
    auto move_direction { Direction::Orthogonal_directions[random_direction_index] };
    move(move_direction);
    m_last_move_direction = move_direction;

    return Action_result::success;
}
