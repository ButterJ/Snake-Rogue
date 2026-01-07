// Use SDL_MAIN_USE_CALLBACK to replace the main function with specific SDL functions
#define SDL_MAIN_USE_CALLBACKS 1

#include "game.h"
#include "game_layer.h"
#include "sdl_manager.h"

#include <SDL3/SDL_main.h>

Core::Game game {};
uint64_t start_time {}; // TODO: Just for testing

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    start_time = SDL_GetTicks();
    game.push_layer<Game_layer>();
    game.start();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    game.update();

    uint64_t current_time { SDL_GetTicks() };
    float elapsed_time { (current_time - start_time) / 1000.0f }; // convert to seconds (from milliseconds)

    if (elapsed_time >= 15.0f)
    {
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    return Sdl_manager::get_instance().handle_event(event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    game.stop();
}
