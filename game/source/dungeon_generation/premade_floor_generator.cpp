#include "premade_floor_generator.h"
#include "environment_object.h"
#include "game_object.h"

#include <experimental/mdspan>
#include <memory>

const std::shared_ptr<Floor> Premade_floor_generator::generate_floor(int floor_rows, int floor_columns) // TODO: This function cannot be resused right now
{
    this->floor_rows = floor_rows;
    this->floor_columns = floor_columns;

    tiles.reserve(floor_rows * floor_columns);

    for (int row = 0; row < floor_rows; ++row)
    {
        for (int column = 0; column < floor_columns; ++column)
        {
            tiles.emplace_back(std::make_shared<Tile>());

            if (row == 0 || row == floor_rows - 1 || column == 0 || column == floor_columns - 1)
            {
                place_wall(row, column);
                continue;
            }

            place_floor(row, column);
        }
    }

    std::shared_ptr<Floor> floor = std::make_shared<Floor>(tiles, floor_rows, floor_columns);

    return floor;
}

void Premade_floor_generator::place_wall(int row, int column)
{
    auto transform_component = std::make_shared<Transform_component>(Position { column, row });
    Sprite_specification sprite_specification { brogue_tiles.get_sprite_specification(3, 2) }; // TODO: Get rid of magic numbers
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    std::shared_ptr<Environment_object> wall { std::make_shared<Environment_object>(Environment_object { Environment_object::Type::wall, transform_component, sprite_component }) };

    std::mdspan tile_view { tiles.data(), floor_rows, floor_columns };
    tile_view[std::array { row, column }].get()->add_game_object(Tile::Occupant_type::environment_object, std::dynamic_pointer_cast<Game_object>(wall));
}

void Premade_floor_generator::place_floor(int row, int column)
{
    auto transform_component = std::make_shared<Transform_component>(Position { column, row });
    Sprite_specification sprite_specification { brogue_tiles.get_sprite_specification(0, 8) }; // TODO: Get rid of magic numbers
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    std::shared_ptr<Environment_object> floor { std::make_shared<Environment_object>(Environment_object { Environment_object::Type::floor, transform_component, sprite_component }) };

    std::mdspan tile_view { tiles.data(), floor_rows, floor_columns };
    tile_view[std::array { row, column }].get()->add_game_object(Tile::Occupant_type::environment_object, std::dynamic_pointer_cast<Game_object>(floor));
}
