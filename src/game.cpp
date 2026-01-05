#include "game.h"
#include "sdl_manager.h"

void Game::initialize()
{
    previous_time = SDL_GetTicks();
    sdl_manager.initialize();
}

void Game::update()
{
    uint64_t current_time { SDL_GetTicks() };
    float delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)
    previous_time = current_time;
    snake.update(delta_time);

    sdl_manager.update();
    sdl_manager.draw_snake(snake);
}

void Game::cleanup()
{
    sdl_manager.cleanup();
}
