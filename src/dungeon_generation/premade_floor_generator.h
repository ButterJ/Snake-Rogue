#pragma once

#include "i_floor_generator.h"
#include <memory>

class Premade_floor_generator : public I_floor_generator
{
  public:
    const std::unique_ptr<Floor> generate_floor() const override;
};
