#include "floor.h"

const std::vector<Tile>& Floor::get_tiles() const
{
    return tiles;
}

const int Floor::get_rows() const
{
    return rows;
}

const int Floor::get_columns() const
{
    return columns;
}
