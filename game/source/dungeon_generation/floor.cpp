#include "floor.h"

#include <experimental/mdspan>

Floor::Floor(std::vector<std::shared_ptr<Tile>> tiles, int rows, int columns)
    : m_tiles { tiles }
    , m_rows { rows }
    , m_columns { columns }
{
}

const std::vector<std::shared_ptr<Tile>>& Floor::get_tiles() const
{
    return m_tiles;
}

std::shared_ptr<Tile> Floor::get_tile_at_position(const Position& position) const // TODO: Handle case where a tile with an invalid position gets requested
{
    std::mdspan tile_view { m_tiles.data(), m_rows, m_columns };

    return tile_view[std::array { position.y, position.x }];
}

bool Floor::is_tile_occupied(const Position& position) const
{
    std::mdspan tile_view { m_tiles.data(), m_rows, m_columns };

    return tile_view[std::array { position.y, position.x }]->is_occupied();
}
