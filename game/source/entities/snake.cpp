#include "snake.h"
#include "sdl_manager.h" //TODO: Temporary!
#include <SDL3/SDL_keyboard.h>
#include <string>

Snake::Snake(int number_of_body_parts, Sprite_renderer& p_sprite_renderer, Sprite_specification p_sprite_specification)
    : sprite_renderer { p_sprite_renderer }, sprite_specification { p_sprite_specification }
{
    current_energy = turn_energy_cost; // So that the player is first. // TODO: Might need to change this

    for (int i = 0; i < number_of_body_parts; i++)
    {
        add_body_part();
    }
}

void Snake::add_body_part()
{
    auto transform_component = std::make_shared<Transform_component>();
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    auto body_part = std::make_shared<Body_part>(sprite_component, transform_component);
    body_parts.push_back(body_part);

    sprite_renderer.register_sprite_component(sprite_component);
}

const std::list<std::shared_ptr<Body_part>>& Snake::get_body_parts() const
{
    return body_parts;
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
}
