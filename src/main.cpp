#include "game.h"
#include "sdl_manager.h"
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

// TODO: Consider doing dungeon generators with strategy pattern
int main(int, char**)
{
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
