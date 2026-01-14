#include "sdl_manager.h"

#include <SDL3/SDL_log.h>
#include <SDL3_image/SDL_image.h>
#include <string>

namespace Core
{

    void Sdl_manager::initialize() // TODO: Rewrite error handling, orient on the SDL CreateWindowAndRenderer documentation
                                   // TODO: Maybe make a function call_sdl_function which will take a function pointer and throw errors.
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

    SDL_Texture& Sdl_manager::get_texture(std::filesystem::path file_path)
    {
        if (loaded_textures.contains(file_path))
        {
            return *loaded_textures[file_path];
        }

        SDL_Texture* loaded_texture { load_texture(file_path) };

        return *loaded_texture;
    }

    SDL_Texture* Sdl_manager::load_texture(std::filesystem::path file_path)
    {
        SDL_Texture* loaded_texture { IMG_LoadTexture(state.renderer, file_path.string().c_str()) };
        loaded_textures[file_path] = loaded_texture;

        return loaded_texture;
    }

    void Sdl_manager::cleanup()
    {
        SDL_DestroyRenderer(state.renderer);
        SDL_DestroyWindow(state.window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
    }

} // namespace Core
