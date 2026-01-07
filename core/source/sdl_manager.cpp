#include "sdl_manager.h"

#include <string>

namespace Core
{

void Sdl_manager::initialize()
{
    try
    {
        SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
        SDL_SetAppMetadata("Snake Rogue", "0.1.0", "Snake Rogue");
        SDL_InitSubSystem(SDL_INIT_VIDEO);
        create_window_and_renderer();
        SDL_SetRenderLogicalPresentation(state.renderer, state.window_specification.logical_width, state.window_specification.logical_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }
    catch (std::string error_message)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error_message.c_str(), nullptr);
        // TODO: Add error handling logger class call.
    }
}

void Sdl_manager::create_window_and_renderer()
{
    if (!SDL_CreateWindowAndRenderer(state.window_specification.window_name, state.window_specification.window_width, state.window_specification.window_height, SDL_WINDOW_RESIZABLE, &state.window, &state.renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        cleanup();
    }
}

const SDL_AppResult Sdl_manager::handle_event(const SDL_Event* const event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
        {
            return SDL_APP_SUCCESS;
        }
        case SDL_EVENT_WINDOW_RESIZED:
        {
            set_window_dimensions(event->window.data1, event->window.data2);
        }
    }

    return SDL_APP_CONTINUE;
}

void Sdl_manager::set_window_dimensions(int windowWidth, int windowHeight)
{
    state.window_specification.window_width = windowWidth;
    state.window_specification.window_height = windowHeight;
}

const Sdl_manager::State& Sdl_manager::get_state() const
{
    return state;
}

void Sdl_manager::cleanup()
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

} // namespace Core
