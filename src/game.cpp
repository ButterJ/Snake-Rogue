#include "game.h"
#include "sdl_manager.h"

void Game::initialize()
{
    previous_time = SDL_GetTicks();
    sdl_manager.initialize();
    time_system.register_entity(snake);
    time_system.register_entity(enemy);
}

void Game::update()
{
    process_turn();

    sdl_manager.update();
    sdl_manager.draw_snake(snake);
}

void Game::process_turn()
{
    update_delta_time();
    if (is_waiting_for_input_cooldown())
    {
        current_input_delay += delta_time;
        return;
    }

    if (!is_player_turn)
    {
        Time_system::Process_result process_result { time_system.process_entity_turns() };

        if (process_result == Time_system::Process_result::require_player_input)
        {
            is_player_turn = true;
        }
    }

    if (is_player_turn)
    {
        Player_controlled_entity::Input_result input_result { snake->process_input() }; // TODO: This should be done for all player controlled entities

        if (input_result == Player_controlled_entity::Input_result::turn_finished) // TODO: Consider turning body into a function
        {
            is_player_turn = false;
            current_input_delay = 0.0f;
        }
    }
}

void Game::update_delta_time()
{
    uint64_t current_time { SDL_GetTicks() };
    delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)
    previous_time = current_time;
}

const bool Game::is_waiting_for_input_cooldown() const
{
    return current_input_delay < delay_after_input;
}

void Game::cleanup()
{
    sdl_manager.cleanup();
}
