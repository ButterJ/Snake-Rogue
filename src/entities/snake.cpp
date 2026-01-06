#include "snake.h"
#include "game.h"
#include "sdl_manager.h" //TODO: Temporary!
#include <SDL3/SDL_keyboard.h>
#include <string>

const std::list<Body_part>& Snake::get_body_parts() const
{
    return body_parts;
}

void Snake::move(const Direction& direction) // TODO: Shouldnt be able to move without body parts (being dead)
{
    Body_part& head { body_parts.front() };
    Position previous_part_position { head.get_position() };
    Position new_position = head.get_position() + direction;
    head.set_position(new_position);

    if (body_parts.size() <= 1)
    {
        return;
    }

    // Move other parts after head
    for (std::list<Body_part>::iterator i { ++body_parts.begin() }; i != body_parts.end(); i++)
    {
        Position temporary_position { previous_part_position };
        previous_part_position = i->get_position();
        i->set_position(temporary_position);
    }
}

Snake::Input_result Snake::process_input()
{
    // Sdl_manager& sdl_manager { Sdl_manager::get_instance() };

    // std::string display_text { "Input timer: " + std::to_string(input_timer) };
    // sdl_manager.add_debug_text(display_text);

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

void Snake::take_turn()
{
    Game::get_instance().set_player_turn();
}
