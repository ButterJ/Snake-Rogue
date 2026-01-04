#pragma once

#include "singleton.h"
#include "snake.h"

class Game : public Singleton<Game>
{
  public:
    void initialize();
    void update(float delta_time);
    void cleanup();

  private:
    Snake snake { 3 }; // TODO: Move this
};
