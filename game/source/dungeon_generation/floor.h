#pragma once

#include "environment_object.h"
#include "vector"

class Floor
{
  public:
    Floor(std::vector<Environment_object> p_tiles, std::vector<int> p_collision_map, int p_rows, int p_columns) : tiles { p_tiles }, collsion_map { p_collision_map }, rows { p_rows }, columns { p_columns } {}

    const std::vector<Environment_object>& get_tiles() const;
    bool is_occupied(const Position& position) const;

  private:
    std::vector<Environment_object> tiles {};
    std::vector<int> collsion_map {};
    const int rows;
    const int columns;

  public:
    int id {};
};
