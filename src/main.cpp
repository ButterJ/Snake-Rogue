#define SDL_MAIN_USE_CALLBACKS 1

#include "game.h"
#include "sdl_manager.h"
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <cstdint>
#include <iostream>

// Use SDL_MAIN_USE_CALLBACK to replace the main function with specific SDL functions

uint64_t previous_time {}; // TODO: This shouldn't be a global variable. Write a time manager or something instead

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    previous_time = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

// This is the new main() function
SDL_AppResult SDL_AppIterate(void* appstate)
{
    Game& game { Game::get_instance() };

    uint64_t current_time { SDL_GetTicks() };
    float delta_time = (current_time - previous_time) / 1000.0f; // convert to seconds (from milliseconds)

    game.update(delta_time);
    previous_time = current_time;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{

    switch (event->type)
    {
    case SDL_EVENT_QUIT:
    {
        return SDL_APP_SUCCESS;
    }
    case SDL_EVENT_WINDOW_RESIZED:
    {
        Sdl_manager& sdl_manager { Sdl_manager::get_instance() };
        sdl_manager.set_window_dimensions(event->window.data1, event->window.data2);
    }
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    Game& game { Game::get_instance() };
    game.cleanup();
}
