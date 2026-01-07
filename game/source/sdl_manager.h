#pragma once

#include "singleton.h"
#include "snake.h"
#include "tile.h"
#include <SDL3/SDL.h>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Sdl_manager : public Singleton<Sdl_manager>
{
  private:
    struct Window_specification
    {
        const char* window_name { "Snake Rogue" };
        int window_width { 1600 };
        int window_height { 900 };
        int logical_width { 640 };
        int logical_height { 320 };
    };

    struct Sdl_state
    {
        SDL_Window* window {};
        SDL_Renderer* renderer {};
        Window_specification window_specification {};
    };

  public:
    void initialize();
    const SDL_AppResult handle_event(const SDL_Event* const event);
    void cleanup();
    void update();
    void draw_snake(const std::shared_ptr<Snake> snake) const;
    void add_debug_text(std::string debug_text);

  private: // TODO: Need to clean up temporary things!
    void create_window_and_renderer();

    void set_window_dimensions(int windowWidth, int windowHeight);
    void render_map_tiles();
    void render_debug_texts();
    void load_textures();
    void destroy_textures();

    Sdl_state state {};
    std::vector<std::string> debug_texts {};

    SDL_Texture* tilemap_texture {};
    const SDL_FRect get_tile_source_rectangle(int horizontal, int vertical) const;

    const float tile_width { 128.0f };
    const float tile_height { 232.0f };
    const int tile_number_horizontal { 16 };
    const int tile_number_vertical { 24 };
};
