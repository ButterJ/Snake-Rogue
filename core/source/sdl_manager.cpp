#include "sdl_manager.h"

#include <SDL3/SDL_log.h>
#include <SDL3_image/SDL_image.h>

#include <string>

namespace Core
{

    void Sdl_manager::initialize()
    {
        try
        {
            SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);

            if (!SDL_SetAppMetadata("Snake Rogue", "0.1.0", "Snake Rogue"))
            {
                throw SDL_GetError();
            }

            if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
            {
                throw SDL_GetError();
            }

            if (!SDL_CreateWindowAndRenderer(m_state.window_specification.window_name, m_state.window_specification.window_width, m_state.window_specification.window_height, SDL_WINDOW_RESIZABLE, &m_state.window, &m_state.renderer))
            {
                throw SDL_GetError();
            }

            if (!SDL_SetRenderLogicalPresentation(m_state.renderer, m_state.window_specification.logical_width, m_state.window_specification.logical_height, SDL_LOGICAL_PRESENTATION_LETTERBOX))
            {
                throw SDL_GetError();
            }
        }
        catch (char* error_message)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error_message, nullptr);
            throw error_message;
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
        m_state.window_specification.window_width = windowWidth;
        m_state.window_specification.window_height = windowHeight;
    }

    const Sdl_manager::State& Sdl_manager::get_state() const
    {
        return m_state;
    }

    SDL_Texture& Sdl_manager::get_texture(std::filesystem::path file_path)
    {
        if (m_loaded_textures.contains(file_path))
        {
            return *m_loaded_textures[file_path];
        }

        SDL_Texture* loaded_texture { load_texture(file_path) };
        SDL_SetTextureScaleMode(loaded_texture, SDL_SCALEMODE_PIXELART); // TODO: Might want different scale modes for different textures

        return *loaded_texture;
    }

    SDL_Texture* Sdl_manager::load_texture(std::filesystem::path file_path)
    {
        SDL_Texture* loaded_texture { IMG_LoadTexture(m_state.renderer, file_path.string().c_str()) };
        m_loaded_textures[file_path] = loaded_texture;

        return loaded_texture;
    }

    void Sdl_manager::destroy_loaded_textures()
    {
        for (auto loaded_texture_pair : m_loaded_textures)
        {
            SDL_DestroyTexture(loaded_texture_pair.second);
        }

        m_loaded_textures.clear();
    }

    void Sdl_manager::cleanup()
    {
        SDL_DestroyRenderer(m_state.renderer);
        SDL_DestroyWindow(m_state.window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        destroy_loaded_textures();
        SDL_Quit();
    }

} // namespace Core
