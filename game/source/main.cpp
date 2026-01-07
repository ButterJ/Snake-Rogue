// Use SDL_MAIN_USE_CALLBACK to replace the main function with specific SDL functions
#define SDL_MAIN_USE_CALLBACKS 1

#include "game.h"
#include "game_layer.h"
#include "sdl_manager.h"

#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    Core::Game::get_instance().push_layer<Game_layer>();
    Core::Game::get_instance().start();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    Core::Game::get_instance().update();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    return Core::Game::get_instance().get_sdl_manager().handle_event(event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    Core::Game::get_instance().stop();
}
