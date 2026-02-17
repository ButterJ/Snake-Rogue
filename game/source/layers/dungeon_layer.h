#pragma once

#include "layer.h"

#include "floor.h"
#include "player_snake.h"
#include "premade_floor_generator.h"
#include "simple_enemy.h"
#include "turn_based_system.h"

#include <memory>

class Dungeon_layer : public Core::Layer
{
  public:
    void on_start() override;
    void on_update(float delta_time) override;
    void on_render() override;
    void on_stop() override;

    std::shared_ptr<Floor> get_current_floor();

  private:
    void render_map_tiles();

    std::shared_ptr<Player_snake> m_snake {};
    std::shared_ptr<Simple_enemy> m_enemy_01 {};
    std::shared_ptr<Simple_enemy> m_enemy_02 {};

    Turn_based_system m_turn_based_system {};

    std::unique_ptr<Premade_floor_generator> m_premade_floor_generator { std::make_unique<Premade_floor_generator>() };
    std::shared_ptr<Floor> m_current_floor;
};
