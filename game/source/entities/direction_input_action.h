#pragma once

#include "input_action.h"

#include "direction.h"

// TODO: Split up into header and source
class Direction_input_action : public Input_action
{
  public:
    Direction_input_action(Direction direction)
        : m_direction { direction }
    {
    }

    const Direction get_direction() const { return m_direction; } // TODO: Consider returning const reference

  private:
    Direction m_direction;
};
