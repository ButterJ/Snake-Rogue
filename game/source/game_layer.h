#pragma once

#include "enemy.h"
#include "game.h"
#include "layer.h"
#include "sdl_manager.h"
#include "snake.h"
#include "time_system.h"

#include <string>

class Game_layer : public Core::Layer
{
  public: // TODO: Rename these function to on_...
    void on_start() override;
    void on_update(float delta_time) override;
    void on_render() override;
    void on_stop() override;

    void add_debug_text(std::string debug_text);

  private:
    void process_turn();
    void update_delta_time();
    const bool is_waiting_for_input_cooldown() const;

    const Core::Sdl_manager::State& sdl_manager_state { Core::Game::get_instance().get_sdl_manager().get_state() };

    bool is_player_turn { true };
    uint64_t previous_time {};
    Time_system time_system {};

    float delta_time {};
    const float delay_after_input { 0.1f }; // TODO: Consider moving this
    float current_input_delay { 0.0f };
    std::shared_ptr<Snake> snake { std::make_shared<Snake>(3) }; // TODO: Move this
    std::shared_ptr<Enemy> enemy { std::make_shared<Enemy>() };

    // TODO: Needs to move
    void render_map_tiles();
    void render_debug_texts();
    void draw_snake(const std::shared_ptr<Snake> snake) const;

    void load_textures();
    void destroy_textures();

    SDL_Texture* tilemap_texture {};

    const SDL_FRect get_tile_source_rectangle(int horizontal, int vertical) const;

    std::vector<std::string> debug_texts {};

    const float tile_width { 128.0f };
    const float tile_height { 232.0f };
    const int tile_number_horizontal { 16 };
    const int tile_number_vertical { 24 };
};
