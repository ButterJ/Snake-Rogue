#include "snake.h"
#include "dungeon_layer.h"
#include "floor.h"

#include <SDL3/SDL_keyboard.h>

void Snake::set_position(const Position& position) // TODO: Think about how to not stack all body parts on each other
{
    if (body_parts.empty())
    {
        return;
    }

    // Set head position
    Body_part* head { body_parts.front().get() };
    head->get_transform_component().get()->position = position;

    if (body_parts.size() <= 1)
    {
        return;
    }

    // Set other body parts positions to the same as head
    for (auto i { ++body_parts.begin() }; i != body_parts.end(); i++)
    {
        i->get()->get_transform_component().get()->position = position;
    }
}

Action_result Snake::move(const Direction& direction) // TODO: Shouldnt be able to move without body parts (being dead)
                                                      // TODO: Also clean up this whole pointer syntax mess
                                                      // TODO: Use the body_part.move(Direction) functionality
{
    Body_part* head { body_parts.front().get() };

    Position previous_part_position { head->get_transform_component().get()->position };

    Position move_position = previous_part_position + direction;

    bool is_move_position_occupied { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->is_occupied(move_position) };

    if (is_move_position_occupied)
    {
        return Action_result::failure;
    }

    head->get_transform_component().get()->position = move_position;

    if (body_parts.size() <= 1)
    {
        return Action_result::success;
    }

    // Move other parts after head
    for (auto i { ++body_parts.begin() }; i != body_parts.end(); i++)
    {
        Position temporary_position { previous_part_position };
        previous_part_position = i->get()->get_transform_component().get()->position;
        i->get()->get_transform_component().get()->position = temporary_position;
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
