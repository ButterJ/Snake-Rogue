#pragma once

#include "component.h"
#include "position.h"

class Transform_component : public Component
{
  public:
    Transform_component() = default;
    Transform_component(Position p_position) : position { p_position } {}

    Position position {};
};
