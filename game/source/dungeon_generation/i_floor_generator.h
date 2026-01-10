#pragma once

#include "floor.h"
#include <memory>

class I_floor_generator
{
  public:
    virtual ~I_floor_generator() {}

    virtual const std::shared_ptr<Floor> generate_floor(int floor_rows, int floor_columns) = 0;

  protected:
    std::vector<Tile> tiles {};
    std::vector<int> collision_map {};
};
