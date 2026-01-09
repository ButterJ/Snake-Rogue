#pragma once

#include <SDL3/SDL.h>

#include <filesystem>
#include <map>

namespace Core
{

    class Sdl_manager
    {
      public:
        struct Window_specification
        {
            const char* window_name { "Snake Rogue" };
            int window_width { 1600 };
            int window_height { 900 };
            int logical_width { 640 };
            int logical_height { 320 };
        };

        struct State
        {
            SDL_Window* window {};
            SDL_Renderer* renderer {};
            Window_specification window_specification {};
        };

        void initialize();
        const SDL_AppResult handle_event(const SDL_Event* const event);
        void cleanup();

        const State& get_state() const;
        SDL_Texture& get_texture(std::filesystem::path file_path);

      private:
        void create_window_and_renderer();
        void set_window_dimensions(int windowWidth, int windowHeight);
        SDL_Texture* load_texture(std::filesystem::path file_path);

        State state {};

        std::map<std::filesystem::path, SDL_Texture*> loaded_textures {};
    };

} // namespace Core
