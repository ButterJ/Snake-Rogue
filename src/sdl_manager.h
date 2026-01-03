#pragma once

#include "singleton.h"
#include "tile.h"
#include <SDL3/SDL.h>
#include <array>
#include <cstddef>

class Sdl_manager : public Singleton<Sdl_manager>
{
  private:
    struct Sdl_state
    {
        SDL_Window* window {};
        SDL_Renderer* renderer {};
        int window_width {1600};
        int window_height {900};
        int logical_width {640};
        int logical_height {320};
        const char* window_name {"Snake Rogue"};
    };

  public:
    void initialize();
    void set_window_dimensions(int windowWidth, int windowHeight);
    void cleanup();
    const int update();

  private:
    void create_window();
    void create_renderer();
    const int handle_sdl_events();

    void render_map_tiles();
    void load_textures();
    void destroy_textures();

    Sdl_state state {};

    // TODO: Temporary! Should be in its own script
    SDL_Texture* tilemap_texture {};
};
