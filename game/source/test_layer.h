#pragma once

#include "layer.h"

#include "game.h"
#include "sdl_manager.h"

#include <SDL3_image/SDL_image.h>

class Test_layer : public Core::Layer
{
  public:
    void on_start() override
    {
        m_test_texture = &m_sdl_manager.get_texture("data/hashtag_01.png");
    }
    void on_update(float delta_time) override {}
    void on_render() override
    {
        SDL_SetRenderDrawColor(m_sdl_state.renderer, 40, 40, 40, 255);
        SDL_RenderClear(m_sdl_state.renderer);

        SDL_FRect source_rectangle { 0, 0, 16, 16 };
        SDL_FRect destination_rectangle { 50, 50, 100, 100 };

        SDL_RenderTexture(m_sdl_state.renderer, m_test_texture, &source_rectangle, &destination_rectangle);
        SDL_RenderPresent(m_sdl_state.renderer);
    }
    void on_stop() override {}

  private:
    Core::Sdl_manager& m_sdl_manager { Core::Game::get_instance().get_sdl_manager() };
    const Core::Sdl_manager::State& m_sdl_state { Core::Game::get_instance().get_sdl_manager().get_state() };
    SDL_Texture* m_test_texture {};
};
