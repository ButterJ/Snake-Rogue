#include "premade_floor_generator.h"
#include "environment_object.h"
#include <mdspan>

const std::shared_ptr<Floor> Premade_floor_generator::generate_floor(int floor_rows, int floor_columns) // TODO: This function cannot be resused right now
{
    this->floor_rows = floor_rows;
    this->floor_columns = floor_columns;

    tiles.reserve(floor_rows * floor_columns);
    collision_map.reserve(floor_rows * floor_columns);

    for (int row = 0; row < floor_rows; ++row)
    {
        for (int column = 0; column < floor_columns; ++column)
        {
            if (row == 0 || row == floor_rows - 1 || column == 0 || column == floor_columns - 1)
            {
                place_wall(row, column);
                continue;
            }

            place_floor(row, column);
        }
    }

    std::shared_ptr<Floor> floor = std::make_shared<Floor>(tiles, collision_map, floor_rows, floor_columns);
    return floor;
}

void Premade_floor_generator::place_wall(int row, int column)
{
    auto transform_component = std::make_shared<Transform_component>(Position { column, row });
    Sprite_specification sprite_specification { brogue_tiles.get_sprite_specification(3, 2) }; // TODO: Get rid of magic numbers
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    Environment_object tile { Environment_object::Type::wall, transform_component, sprite_component };

    tiles.emplace_back(tile);
    collision_map.emplace_back(1);
}

void Premade_floor_generator::place_floor(int row, int column)
{
    auto transform_component = std::make_shared<Transform_component>(Position { column, row });
    Sprite_specification sprite_specification { brogue_tiles.get_sprite_specification(0, 8) }; // TODO: Get rid of magic numbers
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    Environment_object tile { Environment_object::Type::floor, transform_component, sprite_component };

    tiles.emplace_back(tile);
    collision_map.emplace_back(0);
}
