#pragma once

#include "tile.h"
#include "vector"

#include <memory>

class Floor
{
  public:
    Floor(std::vector<std::shared_ptr<Tile>> tiles, int rows, int columns);

    const std::vector<std::shared_ptr<Tile>>& get_tiles() const;
    std::shared_ptr<Tile> get_tile_at_position(const Position& position) const;

    bool is_tile_occupied(const Position& position) const;

  private:
    std::vector<std::shared_ptr<Tile>> m_tiles {};

    const int m_rows;
    const int m_columns;
};
