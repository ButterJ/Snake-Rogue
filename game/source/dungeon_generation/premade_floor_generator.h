#pragma once

#include "i_floor_generator.h"
#include "spritesheet.h"

#include <memory>

class Premade_floor_generator : public I_floor_generator
{
  public:
    const std::shared_ptr<Floor> generate_floor() const override;

  private:
    Spritesheet brogue_tiles { "data/tiles.png", 128.0f, 232.0f }; // TODO: Temporary
};
