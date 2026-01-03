#pragma once

#include "singleton.h"

class Game : public Singleton<Game>
{
public:
  Game();

  const bool get_is_running() const noexcept;
  void update();
  void cleanup();

private:
  bool is_running {true};
};
