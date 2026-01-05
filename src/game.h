#pragma once

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
    uint64_t previous_time {};
    Snake snake { 3 }; // TODO: Move this
};
