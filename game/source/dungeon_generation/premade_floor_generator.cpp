#include "premade_floor_generator.h"
#include "tile.h"
#include <mdspan>

const std::shared_ptr<Floor> Premade_floor_generator::generate_floor() const
{
    constexpr int floor_rows = 14;
    constexpr int floor_columns = 50;

    std::vector<Tile> tiles {};
    tiles.reserve(floor_rows * floor_columns);

    for (int row = 0; row < floor_rows; ++row)
    {
        for (int column = 0; column < floor_columns; ++column)
        {
            Tile::Type tile_type { Tile::Type::floor };

            if (row == 0 || row == floor_rows - 1 || column == 0 || column == floor_columns - 1)
            {
                tile_type = Tile::Type::wall;
            }

            auto transform_component = std::make_shared<Transform_component>();
            transform_component->position = Position { column, row };

            Sprite_specification sprite_specification {};
            if (tile_type == Tile::Type::wall)
            {
                sprite_specification = brogue_tiles.get_sprite_specification(3, 2);
            }
            else if (tile_type == Tile::Type::floor)
            {
                sprite_specification = brogue_tiles.get_sprite_specification(0, 8);
            }

            auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);

            Tile tile { tile_type, transform_component, sprite_component };

            tiles.emplace_back(tile);
        }
    }

    std::shared_ptr<Floor> floor = std::make_shared<Floor>(tiles, floor_rows, floor_columns);

    return floor;

    // std::vector<Tile> tiles(floor_rows * floor_columns, Tile {Tile::Type::floor});

    // std::mdspan tiles_view {tiles.data(), floor_rows, floor_columns}; // TODO: Don't use magic numbers

    // std::size_t rows {tiles_view.extent(0)};
    // std::size_t columns {tiles_view.extent(1)};

    // for (std::size_t row = 0; row != rows; ++row)
    // {
    //     for (std::size_t column = 0; column != columns; ++column)
    //     {
    //         if (row == 0 || row == rows - 1)
    //         {
    //             tiles_view[row, column].type = Tile::Type::wall;
    //         }
    //         else if (column == 0 || column == columns - 1)
    //         {
    //             tiles_view[row, column].type = Tile::Type::wall;
    //         }
    //     }
    // }

    // std::unique_ptr<Floor> floor = std::make_unique<Floor>(tiles, floor_rows, floor_columns);

    return floor;
}
