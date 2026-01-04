#include "game.h"
#include "sdl_manager.h"
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <cstdint>
#include <iostream>

// TODO: Consider doing dungeon generators with strategy pattern
int main(int, char**)
{
    try
    {
        uint64_t previous_time {SDL_GetTicks()};
        Game& game {Game::get_instance()};

        while (game.get_is_running()) // TODO: Should maybe handle this check in the gameloop itself and instead have a game ended event
        {
            uint64_t current_time {SDL_GetTicks()};
            float delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)
            game.update(delta_time);
            previous_time = current_time;
        }

        game.cleanup();
    }
    catch (...) // TODO: Do a proper clean exit
    {
        return 1;
    }

    return 0;
}
