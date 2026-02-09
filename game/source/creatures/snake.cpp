#include "snake.h"
#include "dungeon_layer.h"
#include "floor.h"

#include <SDL3/SDL_keyboard.h>

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
    }

    return Action_result::success;
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
        body_part_to_attack->change_health(-100); // TODO: Replace magic number
        return Action_result::success;
    }

    return Action_result::failure;
}

void Snake::add_body_part(std::shared_ptr<Body_part> body_part)
{
    body_parts.push_back(body_part);
}

void Snake::take_turn()
{
    // Player turns are driven by input in Turn_based_system::update
}
