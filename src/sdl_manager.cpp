#include "sdl_manager.h"
#include "premade_floor_generator.h"
#include "tile.h"
#include <SDL3_image/SDL_image.h>
#include <format>
#include <mdspan>
#include <vector>

void Sdl_manager::initialize()
{
    try
    {
        SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
        SDL_SetAppMetadata("Snake Rogue", "0.1.0", "Snake Rogue");
        SDL_InitSubSystem(SDL_INIT_VIDEO);
        create_window_and_renderer();
        SDL_SetRenderLogicalPresentation(state.renderer, state.logical_width, state.logical_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        load_textures();
    }
    catch (std::string error_message)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error_message.c_str(), nullptr);
        // TODO: Add error handling logger class call.
    }
}

void Sdl_manager::create_window_and_renderer()
{
    if (!SDL_CreateWindowAndRenderer(state.window_name, state.window_width, state.window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &state.window, &state.renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        cleanup();
    }
}

void Sdl_manager::load_textures()
{
    tilemap_texture = IMG_LoadTexture(state.renderer, "data/tiles.png");
    SDL_SetTextureScaleMode(tilemap_texture, SDL_SCALEMODE_NEAREST); // TODO: Consider changing this to SDL_SCALEMODE_PIXELART
}

void Sdl_manager::destroy_textures()
{
    SDL_DestroyTexture(tilemap_texture);
}

void Sdl_manager::update() // TODO: Replace exit codes
{
    SDL_SetRenderDrawColor(state.renderer, 200, 200, 200, 255);
    SDL_RenderClear(state.renderer);

    render_map_tiles();
    render_debug_texts();
}

void Sdl_manager::draw_snake(const Snake& snake) const
{
    const std::list<Body_part>& body_parts = snake.get_body_parts();

    const int body_horizontal_index { 0 };
    const int body_vertical_index { 4 };
    const SDL_FRect source_rectangle { get_tile_source_rectangle(body_horizontal_index, body_vertical_index) };

    for (Body_part body_part : body_parts)
    {
        const Position& position { body_part.get_position() };
        const SDL_FRect destination_rectangle { .x = 12.8f * position.x, .y = 23.2f * position.y, .w = 12.8f, .h = 23.2f };
        SDL_RenderTexture(state.renderer, tilemap_texture, &source_rectangle, &destination_rectangle);
    }

    SDL_RenderPresent(state.renderer);
}

void Sdl_manager::render_map_tiles()
{
    std::unique_ptr<Premade_floor_generator> premade_floor_generator { std::make_unique<Premade_floor_generator>() };
    std::unique_ptr<Floor> generated_floor { premade_floor_generator->generate_floor() };

    const std::vector<Tile>& tiles = generated_floor->get_tiles();
    std::mdspan map_tiles_view { tiles.data(), generated_floor->get_rows(), generated_floor->get_columns() };

    std::size_t rows { map_tiles_view.extents().extent(0) };
    std::size_t columns { map_tiles_view.extents().extent(1) };

    const auto tile_width { 128.0f };
    const auto tile_height { 232.0f };
    const auto tile_number_horizontal { 16 };
    const auto tile_number_vertical { 24 };

    const auto wall_tile_index_horizontal { 3 };
    const auto wall_tile_index_vertical { 2 };
    const auto floor_tile_index_horizontal { 0 };
    const auto floor_tile_index_vertical { 8 };

    // map_tiles_view.data_handle()[1]

    for (std::size_t row = 0; row < rows; ++row)
    {
        for (std::size_t column = 0; column < columns; ++column)
        {
            Tile::Type tile_type { map_tiles_view[row, column].type };

            float source_x {};
            float source_y {};
            if (tile_type == Tile::Type::wall)
            {
                source_x = tile_width * wall_tile_index_horizontal;
                source_y = tile_height * wall_tile_index_vertical;
            }
            else if (tile_type == Tile::Type::floor)
            {
                source_x = tile_width * floor_tile_index_horizontal;
                source_y = tile_height * floor_tile_index_vertical;
            }

            const SDL_FRect source_rectangle { .x = source_x, .y = source_y, .w = tile_width, .h = tile_height };
            const SDL_FRect destination_rectangle { .x = (12.8f * column), .y = (23.2f * row), .w = 12.8f, .h = 23.2f }; // TODO: Don't use magic numbers
            SDL_RenderTexture(state.renderer, tilemap_texture, &source_rectangle, &destination_rectangle);               // TODO: Add check if this function succeeds?
        }
    }
}

const SDL_FRect& Sdl_manager::get_tile_source_rectangle(int horizontal, int vertical) const
{
    const float source_x = tile_width * horizontal;
    const float source_y = tile_height * vertical;
    const SDL_FRect source_rectangle { .x = source_x, .y = source_y, .w = tile_width, .h = tile_height };

    return source_rectangle;
}

void Sdl_manager::render_debug_texts()
{
    for (int i { 0 }; i < debug_texts.size(); i++)
    {
        SDL_RenderDebugText(state.renderer, 50, 50 + 50 * i, debug_texts[i].c_str());
    }

    debug_texts.clear();
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
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

void Sdl_manager::add_debug_text(std::string debug_text)
{
    debug_texts.push_back(debug_text);
}
