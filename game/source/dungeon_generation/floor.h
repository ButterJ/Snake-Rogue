#pragma once

#include "tile.h"
#include "vector"

class Floor
{
  public:
    Floor(std::vector<Tile> p_tiles, std::vector<int> p_collision_map, int p_rows, int p_columns) : tiles { p_tiles }, collsion_map { p_collision_map }, rows { p_rows }, columns { p_columns } {}

    const std::vector<Tile>& get_tiles() const;
    bool is_occupied(const Position& position) const;

  private:
    std::vector<Tile> tiles {};
    std::vector<int> collsion_map {};
    const int rows;
    const int columns;

  public:
    int id {};
};
