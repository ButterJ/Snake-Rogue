#pragma once

#include "enemy.h"
#include "sdl_manager.h"
#include "singleton.h"
#include "snake.h"
#include "time_system.h"
#include <cstdint>
#include <memory>

class Game : public Singleton<Game>
{
  public:
    void initialize();
    void update();
    void cleanup();

  private:
    void process_turn();
    void update_delta_time();
    const bool is_waiting_for_input_cooldown() const;

    bool is_player_turn { true };
    uint64_t previous_time {};
    Sdl_manager& sdl_manager { Sdl_manager::get_instance() };
    Time_system time_system {};

    float delta_time {};
    const float delay_after_input { 0.1f }; // TODO: Consider moving this
    float current_input_delay { 0.0f };
    std::shared_ptr<Snake> snake { std::make_shared<Snake>(3) }; // TODO: Move this
    std::shared_ptr<Enemy> enemy { std::make_shared<Enemy>() };
};
