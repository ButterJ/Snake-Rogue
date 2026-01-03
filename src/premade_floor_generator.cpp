#include "premade_floor_generator.h"
#include "tile.h"
#include <mdspan>

const std::unique_ptr<Floor> Premade_floor_generator::generate_floor() const
{
    constexpr int floor_rows = 3;
    constexpr int floor_columns = 3;
    std::vector<Tile> tiles(floor_rows * floor_columns, Tile {Tile::Type::wall});
    tiles[4] = {Tile::Type::floor};

    std::unique_ptr<Floor> floor = std::make_unique<Floor>(tiles, floor_rows, floor_columns);

    return floor;
}
