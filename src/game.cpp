#include "game.h"
#include "sdl_manager.h"

void Game::initialize()
{
    previous_time = SDL_GetTicks();
    sdl_manager.initialize();
    time_system.register_entity(snake);
}

float input_timer { 0 }; // TODO: Temporary

void Game::update()
{
    uint64_t current_time { SDL_GetTicks() };
    float delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)
    previous_time = current_time;

    if (input_timer < 0.1f)
    {
        input_timer += delta_time;
        return;
    }

    if (state == turn_player)
    {
        Snake::Input_result input_result { snake->process_input() };

        if (input_result == Snake::Input_result::turn_finished)
        {
            state = other;
            input_timer = 0.0f;
        }
    }
    else if (state != turn_player)
    {
        time_system.tick();
    }

    sdl_manager.update();
    sdl_manager.draw_snake(snake);
}

void Game::set_player_turn()
{
    state = turn_player;
}

void Game::cleanup()
{
    sdl_manager.cleanup();
}
