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

    if (key_states[SDL_SCANCODE_W])
    {
        Action_result move_outcome { move(Direction { 0, -1 }) };
        return move_outcome == Action_result::success ? turn_finished : invalid_action;
    }

    if (key_states[SDL_SCANCODE_A])
    {
        Action_result move_outcome { move(Direction { -1, 0 }) };
        return move_outcome == Action_result::success ? turn_finished : invalid_action;
    }

    if (key_states[SDL_SCANCODE_S])
    {
        Action_result move_outcome { move(Direction { 0, 1 }) };
        return move_outcome == Action_result::success ? turn_finished : invalid_action;
    }

    if (key_states[SDL_SCANCODE_D])
    {
        Action_result move_outcome { move(Direction { 1, 0 }) };
        return move_outcome == Action_result::success ? turn_finished : invalid_action;
    }

    return none;
}
