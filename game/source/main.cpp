#define SDL_MAIN_USE_CALLBACKS 1 // Using SDL_MAIN_USE_CALLBACK to replace the main function with specific SDL functions

#include "background_layer.h"
#include "dungeon_layer.h"
#include "game.h"
#include "sdl_manager.h"
#include "test_layer.h"

#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    try
    {
        // Core::Game::get_instance().push_layer<Test_layer>();
        Core::Game::get_instance().push_layer<Background_layer>();
        Core::Game::get_instance().push_layer<Dungeon_layer>();
        Core::Game::get_instance().start();
    }
    catch (...)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Exception caught while starting the app.");
        return SDL_APP_FAILURE;
    }

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
