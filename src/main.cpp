#include "game.h"
#include "sdl_manager.h"
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "floor.h"
#include "premade_floor_generator.h"
#include "tile.h"
#include <cstddef>
#include <iostream>
#include <mdspan>
#include <memory>
#include <print>
#include <vector>

// TODO: Consider doing dungeon generators with strategy pattern
int main(int, char**)
{
    // std::vector v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // // View data as contiguous memory representing 2 rows of 6 ints each
    // auto ms2 = std::mdspan(v.data(), 2, 6);

    // // Write data using 2D view
    // for (std::size_t i = 0; i != ms2.extent(0); i++)
    //     for (std::size_t j = 0; j != ms2.extent(1); j++)
    //         std::println("{} ", ms2[i, j]);

    // std::unique_ptr<Premade_floor_generator> premade_floor_generator {std::make_unique<Premade_floor_generator>()};
    // std::unique_ptr<Floor> generated_floor {premade_floor_generator->generate_floor()};

    // const std::vector<Tile>& tiles = generated_floor->getTiles();
    // std::mdspan tile_view {tiles.data(), 3, 3};

    // for (std::size_t row = 0; row != tile_view.extents().extent(0); ++row)
    // {
    //     for (std::size_t column = 0; column != tile_view.extents().extent(1); ++column)
    //     {
    //         Tile tile = tile_view[row, column];
    //         // std::string tile_print {}
    //         std::println("2");
    //     }
    // }

    // return 0;

    try
    {
        Game& game {Game::get_instance()};

        while (game.get_is_running()) // TODO: Should maybe handle this check in the gameloop itself and instead have a game ended event
        {
            game.update();
        }

        game.cleanup();
    }
    catch (...) // TODO: Do a proper clean exit
    {
        return 1;
    }

    return 0;
}
