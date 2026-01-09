#pragma once

#include "floor.h"
#include <memory>

class I_floor_generator
{
  public:
    virtual ~I_floor_generator() {}

    virtual const std::shared_ptr<Floor> generate_floor() const = 0;
};
