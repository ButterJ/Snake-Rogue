#include "game.h"
#include "sdl_manager.h"

void Game::initialize()
{
    previous_time = SDL_GetTicks();
    Sdl_manager::get_instance().initialize();
}

void Game::update()
{
    uint64_t current_time { SDL_GetTicks() };
    float delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)
    previous_time = current_time;
    snake.update(delta_time);

    Sdl_manager& sdl_manager { Sdl_manager::get_instance() };
    sdl_manager.update();
    sdl_manager.draw_snake(snake);
}

void Game::cleanup()
{
    Sdl_manager& sdl_manager { Sdl_manager::get_instance() };
    sdl_manager.cleanup();
}
