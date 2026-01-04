#pragma once

#include "body_part.h"
#include "direction.h"
#include <list>

class Snake
{
  public:
    Snake(int number_of_body_parts)
        : body_parts {Body_part {Position {1, 1}}, Body_part {Position {2, 1}}, Body_part {Position {2, 2}}}
    {
    }

    void update(float delta_time);
    const std::list<Body_part>& get_body_parts() const;
    void move(const Direction& direction);

  private:
    std::list<Body_part> body_parts {};
    float input_timer {0}; // TODO: Temporary
};
