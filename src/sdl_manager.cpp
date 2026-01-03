#include "sdl_manager.h"

#include <SDL3_image/SDL_image.h>

#include <format>
#include <mdspan>

void Sdl_manager::initialize()
{
  try
  {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    create_window();
    create_renderer();
    SDL_SetRenderLogicalPresentation(state.renderer, state.logical_width, state.logical_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    load_textures();
  }
  catch (std::string error_message)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error_message.c_str(), nullptr);
    // TODO: Add error handling logger class call.
  }
}

void Sdl_manager::create_window()
{
  state.window = SDL_CreateWindow(state.window_name, state.window_width, state.window_height, SDL_WINDOW_RESIZABLE);

  if (!state.window)
  {
    const char* error = SDL_GetError();
    std::string error_message = std::format("Error creating window: {}", error);

    throw error_message;
  }
}

void Sdl_manager::create_renderer()
{
  state.renderer = SDL_CreateRenderer(state.window, nullptr);

  if (!state.renderer)
  {
    const char* error = SDL_GetError();
    std::string error_message = std::format("Error creating renderer: {}", error);

    throw error_message;
  }
}

void Sdl_manager::load_textures()
{
  tilemap_texture = IMG_LoadTexture(state.renderer, "data/tiles.png");
  SDL_SetTextureScaleMode(tilemap_texture, SDL_SCALEMODE_NEAREST);
}

void Sdl_manager::destroy_textures()
{
  SDL_DestroyTexture(tilemap_texture);
}

const int Sdl_manager::update() // TODO: Replace exit codes
{
  int event_exit_code = handle_sdl_events();
  if (event_exit_code != 0)
  {
    return event_exit_code;
  }

  // Perform drawing commands
  SDL_SetRenderDrawColor(state.renderer, 200, 200, 200, 255);
  SDL_RenderClear(state.renderer);

  render_map_tiles();
  //  SDL_FRect src {.x = 0, .y = 0, .w = 16, .h = 16};

  // SDL_FRect dst {.x = 0, .y = 0, .w = 32, .h = 32};

  // SDL_RenderTexture(state.renderer, tileTexture, &src, &dst);

  SDL_RenderPresent(state.renderer);

  return 0; // SDL steps finished normally
}

void Sdl_manager::render_map_tiles()
{
  std::mdspan map_tiles_view {map_tiles.data(), 3, 3}; // TODO: Don't use magic numbers

  std::size_t rows {map_tiles_view.extents().extent(0)};
  std::size_t columns {map_tiles_view.extents().extent(1)};

  const auto tile_width {128.0f};
  const auto tile_height {232.0f};
  const auto tile_number_horizontal {16};
  const auto tile_number_vertical {24};

  const auto wall_tile_index_horizontal {3};
  const auto wall_tile_index_vertical {2};
  const auto floor_tile_index_horizontal {0};
  const auto floor_tile_index_vertical {8};

  // map_tiles_view.data_handle()[1]

  for (std::size_t row = 0; row < rows; ++row)
  {
    for (std::size_t column = 0; column < columns; ++column)
    {
      // auto source_tile_position_x {map_tiles_view[row, column]}

      const SDL_FRect source_rectangle {.x = 0, .y = 5336, .w = 128, .h = 232};                                  // TODO: Don't use magic numbers
      const SDL_FRect destination_rectangle {.x = (12.8f * row), .y = (23.2f * column), .w = 12.8f, .h = 23.2f}; // TODO: Don't use magic numbers
      SDL_RenderTexture(state.renderer, tilemap_texture, &source_rectangle, &destination_rectangle);             // TODO: Add check if this function succeeds?
    }
  }
}

const int Sdl_manager::handle_sdl_events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
    {
      return 1; // SDL Quit
    }
    case SDL_EVENT_WINDOW_RESIZED:
    {
      set_window_dimensions(event.window.data1, event.window.data2);
    }
    }
  }
}

void Sdl_manager::set_window_dimensions(int windowWidth, int windowHeight)
{
  state.window_width = windowWidth;
  state.window_height = windowHeight;
}

void Sdl_manager::cleanup()
{
  destroy_textures();
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(state.window);
  SDL_Quit();
}
