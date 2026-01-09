#include "game_layer.h"
#include "floor.h"
#include "premade_floor_generator.h"
#include "sdl_manager.h"
#include "sprite_component.h"
#include "transform_component.h"
#include <SDL3_image/SDL_image.h>
#include <mdspan>

void Game_layer::on_start()
{
    previous_time = SDL_GetTicks();

    time_system.register_entity(snake);

    auto sprite_component_enemy = std::make_shared<Sprite_component>();
    auto transform_component_enemy = std::make_shared<Transform_component>();

    enemy = std::make_shared<Enemy>(sprite_component_enemy, transform_component_enemy);

    time_system.register_entity(enemy);
    load_textures();
}

void Game_layer::on_update(float delta_time)
{
    process_turn();
}

void Game_layer::on_render() // TODO
{
    SDL_SetRenderDrawColor(sdl_manager_state.renderer, 200, 200, 200, 255);
    SDL_RenderClear(sdl_manager_state.renderer);

    render_map_tiles();
    draw_snake(snake);
    render_debug_texts();
    SDL_RenderPresent(sdl_manager_state.renderer);
}

void Game_layer::load_textures()
{
    tilemap_texture = IMG_LoadTexture(sdl_manager_state.renderer, "data/tiles.png");
    SDL_SetTextureScaleMode(tilemap_texture, SDL_SCALEMODE_NEAREST); // TODO: Consider changing this to SDL_SCALEMODE_PIXELART
}

void Game_layer::destroy_textures()
{
    SDL_DestroyTexture(tilemap_texture);
}

void Game_layer::render_map_tiles()
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
            SDL_RenderTexture(sdl_manager_state.renderer, tilemap_texture, &source_rectangle, &destination_rectangle);   // TODO: Add check if this function succeeds?
        }
    }
}

void Game_layer::draw_snake(const std::shared_ptr<Snake> snake) const
{
    const auto body_parts = snake->get_body_parts();

    const int body_horizontal_index { 0 };
    const int body_vertical_index { 4 };
    const SDL_FRect source_rectangle { get_tile_source_rectangle(body_horizontal_index, body_vertical_index) };

    for (const auto& body_part : body_parts)
    {
        const Position& position { body_part->get_position() };
        const SDL_FRect destination_rectangle { .x = 12.8f * position.x, .y = 23.2f * position.y, .w = 12.8f, .h = 23.2f };
        SDL_RenderTexture(sdl_manager_state.renderer, tilemap_texture, &source_rectangle, &destination_rectangle);
    }
}

const SDL_FRect Game_layer::get_tile_source_rectangle(int horizontal, int vertical) const
{
    const float source_x = tile_width * horizontal;
    const float source_y = tile_height * vertical;
    const SDL_FRect source_rectangle { .x = source_x, .y = source_y, .w = tile_width, .h = tile_height };

    return source_rectangle;
}

void Game_layer::render_debug_texts()
{
    for (int i { 0 }; i < debug_texts.size(); i++)
    {
        SDL_RenderDebugText(sdl_manager_state.renderer, 50, 50 + 50 * i, debug_texts[i].c_str());
    }

    debug_texts.clear();
}

void Game_layer::add_debug_text(std::string debug_text)
{
    debug_texts.push_back(debug_text);
}

void Game_layer::on_stop()
{
    destroy_textures();
}

void Game_layer::process_turn()
{
    update_delta_time();
    if (is_waiting_for_input_cooldown())
    {
        current_input_delay += delta_time;
        return;
    }

    if (!is_player_turn)
    {
        Turn_based_system::Process_result process_result { time_system.process_entity_turns() };

        if (process_result == Turn_based_system::Process_result::require_player_input)
        {
            is_player_turn = true;
        }
    }

    if (is_player_turn)
    {
        Player_controlled_entity::Input_result input_result { snake->process_input() }; // TODO: This should be done for all player controlled entities

        if (input_result == Player_controlled_entity::Input_result::turn_finished) // TODO: Consider turning body into a function
        {
            is_player_turn = false;
            current_input_delay = 0.0f;
        }
    }
}

void Game_layer::update_delta_time()
{
    uint64_t current_time { SDL_GetTicks() };
    delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)
    previous_time = current_time;
}

const bool Game_layer::is_waiting_for_input_cooldown() const
{
    return current_input_delay < delay_after_input;
}
