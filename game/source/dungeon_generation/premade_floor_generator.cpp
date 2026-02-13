#include "premade_floor_generator.h"

#include "dirt.h"
#include "environment_object.h"
#include "wall.h"

#include <experimental/mdspan>
#include <memory>

// TODO: This function cannot be resused right now. One floor generator should be able to generate multiple different floors
const std::shared_ptr<Floor> Premade_floor_generator::generate_floor(int floor_rows, int floor_columns)
{
    m_floor_rows = floor_rows;
    m_floor_columns = floor_columns;

    m_tiles.reserve(floor_rows * floor_columns);

    for (int row = 0; row < floor_rows; ++row)
    {
        for (int column = 0; column < floor_columns; ++column)
        {
            m_tiles.emplace_back(std::make_shared<Tile>());

            if (row == 0 || row == floor_rows - 1 || column == 0 || column == floor_columns - 1)
            {
                place_wall(row, column);
                continue;
            }

            place_floor(row, column);
        }
    }

    std::shared_ptr<Floor> floor = std::make_shared<Floor>(m_tiles, floor_rows, floor_columns);

    return floor;
}

void Premade_floor_generator::place_wall(int row, int column)
{
    Position position { column, row };
    std::shared_ptr<Wall> wall { std::make_shared<Wall>(position) };

    std::mdspan tile_view { m_tiles.data(), m_floor_rows, m_floor_columns };
    tile_view[std::array { row, column }].get()->add_game_object(Tile::Occupant_type::environment_object, std::dynamic_pointer_cast<Game_object>(wall));
}

void Premade_floor_generator::place_floor(int row, int column)
{
    Position position { column, row };
    std::shared_ptr<Dirt> dirt { std::make_shared<Dirt>(position) };

    std::mdspan tile_view { m_tiles.data(), m_floor_rows, m_floor_columns };
    tile_view[std::array { row, column }].get()->add_game_object(Tile::Occupant_type::environment_object, std::dynamic_pointer_cast<Game_object>(dirt));
}
