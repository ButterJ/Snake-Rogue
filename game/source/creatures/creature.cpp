#include "creature.h"

#include "direction_input_action.h"
#include "dungeon_layer.h"
#include "floor.h"
#include "player_input_controller.h" // ! TODO temporary for testing, the creature class itself should not have this

Creature::Creature(int number_of_body_parts, const Sprite_specification& sprite_specification)
    : Turn_based_entity(std::make_shared<Player_input_controller>())
    , m_max_body_parts { number_of_body_parts }
    , m_sprite_specification { sprite_specification }
{
    for (int i = 0; i < number_of_body_parts; i++)
    {
        std::shared_ptr<Body_part> body_part { create_body_part() };
        add_body_part(body_part);
    }
}

Action_result Creature::set_position(const Position& position)
{
    if (m_body_parts.empty())
    {
        return Action_result::failure;
    }

    for (auto it { m_body_parts.begin() }; it != m_body_parts.end(); it++)
    {
        Action_result action_result { it->get()->set_position(position) };

        if (action_result == Action_result::failure)
        {
            return action_result;
        }
    }

    return Action_result::success;
}

std::shared_ptr<Body_part> Creature::create_body_part()
{
    auto transform_component = std::make_shared<Transform_component>();

    auto sprite_component = std::make_shared<Sprite_component>(m_sprite_specification, transform_component);
    auto body_part = std::make_shared<Body_part>(sprite_component, transform_component);

    return body_part;
}

void Creature::add_body_part(std::shared_ptr<Body_part> body_part)
{
    m_body_parts.push_back(body_part);
    body_part->On_death_callback.append([this, body_part]()
                                        { on_body_part_death(body_part); });
}

void Creature::on_body_part_death(std::shared_ptr<Body_part> body_part)
{
}

Position Creature::get_head_position() const
{
    bool has_head { m_body_parts.size() != 0 };

    if (has_head)
    {
        return m_body_parts.begin()->get()->get_position();
    }

    return m_last_position;
}

void Creature::perform_input_action(std::shared_ptr<Input_action> input_action)
{
    auto direction_input_action { std::dynamic_pointer_cast<Direction_input_action>(input_action) };

    if (direction_input_action)
    {
        on_direction_input(direction_input_action->get_direction());
    }
}

Action_result Creature::on_direction_input(const Direction& direction)
{
    Action_result move_result { move(direction) };

    if (move_result == Action_result::success)
    {
        return Action_result::success;
    }

    Action_result attack_result { attack(direction) };

    if (attack_result == Action_result::success)
    {
        return Action_result::success;
    }

    return Action_result::failure;
}

Action_result Creature::attack(const Direction& direction)
{
    auto head { m_body_parts.front() };
    auto current_floor { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor() };
    auto tile_to_attack { current_floor->get_tile_at_position(head->get_position() + direction) };

    auto body_part_to_attack { tile_to_attack->get_held_body_part() };

    if (body_part_to_attack)
    {
        auto damage { static_cast<int>(attack_damage.get_value()) };
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, std::to_string(damage).c_str()); // !Temporary
        body_part_to_attack->change_health(-damage);

        return Action_result::success;
    }

    return Action_result::failure;
}

Action_result Creature::move(const Direction& direction)
{
    auto head { m_body_parts.front() };

    auto previous_body_part_position { head->get_transform_component().get()->position + direction };

    for (const auto& body_part : m_body_parts)
    {
        auto body_part_position { body_part.get()->get_transform_component().get()->position };
        auto body_part_move_direction { previous_body_part_position - body_part_position };
        previous_body_part_position = body_part_position;
        Action_result action_result { body_part.get()->move(body_part_move_direction) };

        if (action_result == Action_result::failure)
        {
            return action_result;
        }

        if (body_part == head)
        {
            auto head_position { body_part_position + body_part_move_direction };
            auto head_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(head_position) };
            auto foods_to_eat { head_tile->get_held_foods() };
            eat_foods(foods_to_eat);
            head_tile->remove_game_object(Tile::Occupant_type::food); // TODO: I would like this to be in the eat_foods function
        }
    }

    return Action_result::success;
}

void Creature::eat_foods(std::set<std::shared_ptr<Food>> foods)
{
    for (const auto& food : foods)
    {
        m_satiation_bar.change_value(food->get_satiation_value());
    }
}
