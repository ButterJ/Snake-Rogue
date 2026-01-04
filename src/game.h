#pragma once

#include "singleton.h"
#include "snake.h"

class Game : public Singleton<Game>
{
  public:
    Game();

    const bool get_is_running() const noexcept;
    void update(float delta_time);
    void cleanup();

  private:
    bool is_running {true};
    Snake snake {3}; // TODO: Move this
};
