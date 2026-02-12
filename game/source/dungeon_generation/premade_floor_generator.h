#pragma once

#include "i_floor_generator.h"
#include "spritesheet.h"

#include <memory>

class Premade_floor_generator : public I_floor_generator
{
  public:
    const std::shared_ptr<Floor> generate_floor(int floor_rows, int floor_columns) override;

  private:
    void place_wall(int row, int column);
    void place_floor(int row, int column);

    Spritesheet brogue_tiles { "data/tiles.png", 128.0f, 232.0f }; // TODO: Temporary

    int m_floor_rows {};
    int m_floor_columns {};
};
