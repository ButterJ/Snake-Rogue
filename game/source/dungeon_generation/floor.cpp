#include "floor.h"

#include <experimental/mdspan>

const std::vector<std::shared_ptr<Tile>>& Floor::get_tiles() const
{
    return tiles;
}

std::shared_ptr<Tile> Floor::get_tile_at_position(const Position& position) const // TODO: Handle case where a tile with an invalid position gets requested
{
    std::mdspan tile_view { tiles.data(), rows, columns };

    return tile_view[std::array { position.y, position.x }];
}

bool Floor::is_occupied(const Position& position) const
{
    std::mdspan tile_view { tiles.data(), rows, columns };

    return tile_view[std::array { position.y, position.x }]->is_occupied();
}
