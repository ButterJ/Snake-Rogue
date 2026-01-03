#include "premade_floor_generator.h"
#include "tile.h"
#include <mdspan>

const std::unique_ptr<Floor> Premade_floor_generator::generate_floor() const
{
    constexpr int floor_rows = 50;
    constexpr int floor_columns = 14;
    std::vector<Tile> tiles(floor_rows * floor_columns, Tile {Tile::Type::floor});

    std::mdspan tiles_view {tiles.data(), floor_rows, floor_columns}; // TODO: Don't use magic numbers

    std::size_t rows {tiles_view.extent(0)};
    std::size_t columns {tiles_view.extent(1)};

    for (std::size_t row = 0; row != rows; ++row)
    {
        for (std::size_t column = 0; column != columns; ++column)
        {
            if (row == 0 || row == rows - 1)
            {
                tiles_view[row, column].type = Tile::Type::wall;
            }
            else if (column == 0 || column == columns - 1)
            {
                tiles_view[row, column].type = Tile::Type::wall;
            }
        }
    }

    std::unique_ptr<Floor> floor = std::make_unique<Floor>(tiles, floor_rows, floor_columns);

    return floor;
}
