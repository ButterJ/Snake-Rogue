#include "simple_enemy_input_controller.h"

#include "direction_input_action.h"
#include "dungeon_layer.h"
#include "random_number_generator.h"

Simple_enemy_input_controller::Simple_enemy_input_controller(std::vector<std::shared_ptr<Body_part>>& enemy_body_parts)
    : m_enemy_body_parts { enemy_body_parts }
{
}

// TODO: Clean this up
void Simple_enemy_input_controller::start_deciding_on_action()
{
    std::vector<Direction> adjacent_target_directions {};
    std::vector<Direction> occupied_directions {};

    Position current_position { m_enemy_body_parts.front()->get_position() };

    for (const auto& direction : Direction::Orthogonal_directions)
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

        adjacent_target_directions.push_back(direction); // TODO: Differentiate between target and non target body parts
    }

    if (!adjacent_target_directions.empty())
    {
        int random_direction_index { Random_number_generator::get(0, adjacent_target_directions.size() - 1) };
        auto direction_input_action { std::make_shared<Direction_input_action>(adjacent_target_directions[random_direction_index]) };
        On_action_decided(direction_input_action);
        return;
    }

    move_towards_weighted_random_direction(occupied_directions);
}

// TODO: Handle action failure case properly
Action_result Simple_enemy_input_controller::move_towards_weighted_random_direction(const std::vector<Direction>& occupied_directions)
{
    auto current_floor { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor() };
    Position current_position { m_enemy_body_parts.front()->get_position() };

    std::vector<double> weights {};
    auto opposite_direction_from_last_move { m_last_move_direction.get_opposite_direction() };

    for (const auto& direction : Direction::Orthogonal_directions)
    {
        auto it { std::ranges::find(occupied_directions, direction) };
        if (it != occupied_directions.end())
        {
            weights.emplace_back(0.0);
            continue;
        }

        // Can't move into the opposite direction from the last move direction
        if (direction == opposite_direction_from_last_move)
        {
            weights.emplace_back(0.0);
            continue;
        }

        double direction_weight { 1.0 };
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
    m_last_move_direction = move_direction;

    auto direction_input_action { std::make_shared<Direction_input_action>(move_direction) };
    On_action_decided(direction_input_action);

    return Action_result::success;
}
