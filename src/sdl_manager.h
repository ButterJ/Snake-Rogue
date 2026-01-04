#pragma once

#include "singleton.h"
#include "snake.h"
#include "tile.h"
#include <SDL3/SDL.h>
#include <cstddef>
#include <string>
#include <vector>

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
    void draw_snake(const Snake& snake) const;
    void add_debug_text(std::string debug_text);

  private: // TODO: Need to clean up temporary things!
    void create_window();
    void create_renderer();
    const int handle_sdl_events();

    void render_map_tiles();
    void render_debug_texts();
    void load_textures();
    void destroy_textures();

    Sdl_state state {};
    std::vector<std::string> debug_texts {};

    SDL_Texture* tilemap_texture {};
    const SDL_FRect& get_tile_source_rectangle(int horizontal, int vertical) const;

    const float tile_width {128.0f};
    const float tile_height {232.0f};
    const int tile_number_horizontal {16};
    const int tile_number_vertical {24};
};
