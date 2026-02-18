#pragma once

#include "input_action.h"

#include "direction.h"

class Direction_input_action : public Input_action
{
  public:
    Direction_input_action(Direction direction)
        : m_direction { direction }
    {
    }

    const Direction get_direction() const; // TODO: Consider returning const reference

  private:
    Direction m_direction;
};
