#include "floor.h"

#include <mdspan>

const std::vector<Environment_object>& Floor::get_tiles() const
{
    return tiles;
}

bool Floor::is_occupied(const Position& position) const
{
    std::mdspan collision_map_view { collsion_map.data(), rows, columns };

    return collision_map_view[position.y, position.x] == 1;
}
