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
  // template <typename T, std::size_t Row, std::size_t Col>
  // using Array_flat_2d = std::array<T, Row * Col>;
  template <typename T, std::size_t Row, std::size_t Col>
  using Array2d = std::array<std::array<T, Col>, Row>;
  Array2d<Tile, 3, 3> map_tiles {Tile {Tile::Type::wall},
                                 Tile {Tile::Type::wall},
                                 Tile {Tile::Type::wall},
                                 Tile {Tile::Type::wall},
                                 Tile {Tile::Type::floor},
                                 Tile {Tile::Type::wall},
                                 Tile {Tile::Type::wall},
                                 Tile {Tile::Type::wall},
                                 Tile {Tile::Type::wall}};

  SDL_Texture* tilemap_texture {};
};
