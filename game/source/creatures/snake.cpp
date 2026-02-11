#include "snake.h"
#include "dungeon_layer.h"
#include "floor.h"

#include <SDL3/SDL_keyboard.h>
#include <string>

Snake::Snake(int number_of_body_parts, const Sprite_specification& sprite_specification) : Creature<Player_controlled_entity>(number_of_body_parts, sprite_specification)
{
    satiation_bar.On_bar_filled_callback.append([this]()
                                                { on_satiation_bar_filled(); });
}

Action_result Snake::set_position(const Position& position) // TODO: Think about how to not stack all body parts on each other
{
    if (body_parts.empty())
    {
        return Action_result::failure;
    }

    for (auto i { body_parts.begin() }; i != body_parts.end(); i++)
    {
        Action_result action_result { i->get()->set_position(position) };

        if (action_result == Action_result::failure)
        {
            return action_result;
        }
    }

    return Action_result::success; // TODO: Need to return the correct action result
}

Action_result Snake::move(const Direction& direction)
{
    auto head { body_parts.front() };

    auto previous_body_part_position { head->get_transform_component().get()->position + direction };

    for (auto body_part : body_parts)
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
            head_tile->remove_all_foods(); // TODO: I would like this to be in the eat_foods function
        }
    }

    return Action_result::success;
}

void Snake::eat_foods(std::set<std::shared_ptr<Food>> foods)
{
    for (auto food : foods)
    {
        satiation_bar.change_value(food->get_satiation_value());
    }
}

void Snake::on_satiation_bar_filled()
{
    if (body_parts.size() >= m_max_body_parts)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Leveling up not implemented yet");
        return;
    }

    // TODO: Add body part

    satiation_bar.set_value(0);
}

const Snake::Input_result Snake::process_input()
{
    const bool* key_states = SDL_GetKeyboardState(0); // TODO: Disallow diagonal movement

    Direction direction_input {};
    if (key_states[SDL_SCANCODE_W])
    {
        direction_input += Direction::Up;
    }

    if (key_states[SDL_SCANCODE_A])
    {
        direction_input += Direction::Left;
    }

    if (key_states[SDL_SCANCODE_S])
    {
        direction_input += Direction::Down;
    }

    if (key_states[SDL_SCANCODE_D])
    {
        direction_input += Direction::Right;
    }

    if (direction_input != Direction::Zero)
    {
        return on_direction_input(direction_input);
    }

    return none;
}

Snake::Input_result Snake::on_direction_input(const Direction& direction)
{
    Action_result move_result { move(direction) };

    if (move_result == Action_result::success)
    {
        return turn_finished;
    }

    Action_result attack_result { attack(direction) };

    if (attack_result == Action_result::success)
    {
        return turn_finished;
    }

    return invalid_action; // TODO: See if none is needed to be returned
}

Action_result Snake::attack(const Direction& direction)
{
    auto head { body_parts.front() };
    auto current_floor { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor() };
    auto tile_to_attack { current_floor->get_tile_at_position(head->get_position() + direction) };

    auto body_part_to_attack { tile_to_attack->get_held_body_part() };

    if (body_part_to_attack)
    {
        body_part_to_attack->change_health(-20); // TODO: Replace magic number
        return Action_result::success;
    }

    return Action_result::failure;
}

void Snake::on_body_part_death(std::shared_ptr<Body_part> dead_body_part)
{
    bool dead_body_part_found { false };

    for (auto it { body_parts.begin() }; it != body_parts.end();)
    {
        if (dead_body_part_found)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Removing body part after dead body part");
            // TODO: Instead of this triggering an inefficient chain reaction, continue removing in this for loop.
            // TODO: To do this, the death callback needs to be removed from the body part.
            (*it)->die();
            return;
        }

        if (*it == dead_body_part)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Dead body part found");
            dead_body_part_found = true;
            it = body_parts.erase(it);
            continue;
        }

        it++;
    }
}

void Snake::take_turn()
{
    // Player turns are driven by input in Turn_based_system::update
}
