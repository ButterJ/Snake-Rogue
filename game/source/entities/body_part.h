#pragma once

#include "position.h"

class Body_part
{
  public:
    Body_part(Position p_position)
        : position {p_position}
    {
    }

    const Position& get_position() const;
    void set_position(const Position& position);

  private:
    int health {1};
    Position position {};
};
