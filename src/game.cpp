#include "game.h"
#include "sdl_manager.h"

void Game::initialize()
{
    Sdl_manager::get_instance().initialize();
}

void Game::update(float delta_time)
{
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
