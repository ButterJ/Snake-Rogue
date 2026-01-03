#pragma once

#include "tile.h"
#include "vector"

class Floor
{
  public:
    Floor(std::vector<Tile> p_tiles, int p_rows, int p_columns) : tiles {p_tiles}, rows {p_rows}, columns {p_columns} {}

    const std::vector<Tile>& get_tiles() const;
    const int get_rows() const;
    const int get_columns() const;

  private:
    std::vector<Tile>
        tiles {};
    const int rows;
    const int columns;

  public:
    int id {};
};
