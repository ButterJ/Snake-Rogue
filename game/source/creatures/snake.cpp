#include "snake.h"

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

void Snake::move(const Direction& direction) // TODO: Shouldnt be able to move without body parts (being dead)
                                             // TODO: Also clean up this whole pointer syntax mess
                                             // TODO: Use the body_part.move(Direction) functionality
{
    Body_part* head { body_parts.front().get() };

    Position previous_part_position { head->get_transform_component().get()->position };
    head->get_transform_component().get()->position = previous_part_position + direction;

    if (body_parts.size() <= 1)
    {
        return;
    }

    // Move other parts after head
    for (auto i { ++body_parts.begin() }; i != body_parts.end(); i++)
    {
        Position temporary_position { previous_part_position };
        previous_part_position = i->get()->get_transform_component().get()->position;
        i->get()->get_transform_component().get()->position = temporary_position;
    }
}

const Snake::Input_result Snake::process_input()
{
    const bool* key_states = SDL_GetKeyboardState(0); // TODO: Disallow diagonal movement

    if (key_states[SDL_SCANCODE_W])
    {
        move(Direction { 0, -1 });
        return turn_finished;
    }

    if (key_states[SDL_SCANCODE_A])
    {
        move(Direction { -1, 0 });
        return turn_finished;
    }

    if (key_states[SDL_SCANCODE_S])
    {
        move(Direction { 0, 1 });
        return turn_finished;
    }

    if (key_states[SDL_SCANCODE_D])
    {
        move(Direction { 1, 0 });
        return turn_finished;
    }

    return none;
}
