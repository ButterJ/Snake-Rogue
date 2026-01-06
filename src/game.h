#pragma once

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
    void set_player_turn();

  private:
    enum State
    {
        turn_player,
        other
    };

    State state { turn_player };
    uint64_t previous_time {};
    Sdl_manager& sdl_manager { Sdl_manager::get_instance() };
    Time_system time_system {};
    std::shared_ptr<Snake> snake { std::make_shared<Snake>(3) }; // TODO: Move this
};
