#pragma once

#include "sdl_manager.h"
#include "singleton.h"
#include "snake.h"
#include <cstdint>

class Game : public Singleton<Game>
{
  public:
    void initialize();
    void update();
    void cleanup();

  private:
    // Game() : sdl_manager(Sdl_manager::get_instance()) {}
    // friend class Singleton<Game>;

    uint64_t previous_time {};
    Sdl_manager& sdl_manager { Sdl_manager::get_instance() };
    Snake snake { 3 }; // TODO: Move this
};
