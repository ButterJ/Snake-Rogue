#include "game.h"

#include <SDL3/SDL_timer.h>

namespace Core
{
    void Game::start()
    {
        m_sdl_manager.initialize();

        m_previous_time = SDL_GetTicks();

        for (const std::unique_ptr<Layer>& layer : m_layer_stack)
        {
            layer->on_start();
        }
    }

    void Game::update()
    {
        uint64_t current_time { SDL_GetTicks() };

        float delta_time { (current_time - m_previous_time) / 1000.0f }; // convert to seconds (from milliseconds)
        m_previous_time = current_time;

        for (const std::unique_ptr<Layer>& layer : m_layer_stack)
        {
            layer->on_update(delta_time);
            layer->on_render(); // TODO: Might want to only render at specific times, not every frame
        }
    }

    void Game::stop()
    {
        for (const std::unique_ptr<Layer>& layer : m_layer_stack)
        {
            layer->on_stop();
        }

        m_sdl_manager.cleanup();
    }

    Sdl_manager& Game::get_sdl_manager()
    {
        return m_sdl_manager;
    }

} // namespace Core
