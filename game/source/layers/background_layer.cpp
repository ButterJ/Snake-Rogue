#include "background_layer.h"

#include "game.h"

#include <SDL3/SDL_render.h>

void Background_layer::on_render()
{
    const Core::Sdl_manager::State& sdl_manager_state { Core::Game::get_instance().get_sdl_manager().get_state() };

    SDL_SetRenderDrawColor(sdl_manager_state.renderer, m_background_colour.r, m_background_colour.g, m_background_colour.b, m_background_colour.a);
    SDL_RenderClear(sdl_manager_state.renderer);
}
