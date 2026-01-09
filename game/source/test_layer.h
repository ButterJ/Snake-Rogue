#pragma once

#include "enemy.h"
#include "layer.h"
#include "snake.h"
#include "sprite_component.h"
#include "sprite_renderer.h"
#include "spritesheet.h"
#include "transform_component.h"
#include "turn_based_system.h"

#include <memory>

class Test_layer : public Core::Layer
{
  public:
    void on_start() override;
    void on_update(float delta_time) override;
    void on_render() override;
    void on_stop() override;

  private:
    Spritesheet brogue_tiles { "data/tiles.png", 128.0f, 232.0f };
    Sprite_renderer sprite_renderer {};
    std::shared_ptr<Transform_component> test_transform_component;
    std::shared_ptr<Sprite_component> test_sprite_component;

    std::shared_ptr<Snake> snake;
    std::shared_ptr<Enemy> enemy;

    Turn_based_system turn_based_system {};

    const Core::Sdl_manager::State& sdl_manager_state { Core::Game::get_instance().get_sdl_manager().get_state() };
};
