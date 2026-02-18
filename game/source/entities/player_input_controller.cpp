#include "player_input_controller.h"

#include "direction.h"
#include "direction_input_action.h"
#include "waiting_action.h"

#include <SDL3/SDL_keyboard.h>

void Player_input_controller::start_deciding_on_action()
{
    m_is_listening_to_input = true;
}

void Player_input_controller::process_input()
{
    const bool* key_states = SDL_GetKeyboardState(0); // TODO: Disallow diagonal movement

    if (key_states[SDL_SCANCODE_PERIOD])
    {
        On_action_decided(std::make_shared<Waiting_action>());
        return;
    }

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
        auto direction_input_action { std::make_shared<Direction_input_action>(direction_input) };
        On_action_decided(direction_input_action);
        return;
    }

    return;
}
