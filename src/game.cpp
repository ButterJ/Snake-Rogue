#include "game.h"
#include "sdl_manager.h"

Game::Game()
{
    Sdl_manager& sdl_manager {Sdl_manager::get_instance()};
    sdl_manager.initialize();
}

void Game::update(float delta_time)
{ // TODO: Should maybe check if the game is running
    Sdl_manager& sdl_manager {Sdl_manager::get_instance()};

    snake.update(delta_time);

    int sdl_exit_code = sdl_manager.update(); // TODO: Exit code should be replaced
    sdl_manager.draw_snake(snake);

    if (sdl_exit_code == 1)
    {
        is_running = false;
    }
}

const bool Game::get_is_running() const noexcept
{
    return is_running;
}

void Game::cleanup()
{
    Sdl_manager& sdl_manager {Sdl_manager::get_instance()};
    sdl_manager.cleanup();
}
