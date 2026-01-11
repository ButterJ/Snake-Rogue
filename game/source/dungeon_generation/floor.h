#pragma once

#include "environment_object.h"
#include "tile.h"
#include "vector"

#include <memory>

class Floor
{
  public:
    Floor(std::vector<std::shared_ptr<Tile>> p_tiles, int p_rows, int p_columns) : tiles { p_tiles }, rows { p_rows }, columns { p_columns } {}

    const std::vector<std::shared_ptr<Tile>>& get_tiles() const;
    std::shared_ptr<Tile> get_tile_at_position(const Position& position) const;
    bool is_occupied(const Position& position) const;

  private:
    std::vector<std::shared_ptr<Tile>> tiles {};
    const int rows;
    const int columns;
};
