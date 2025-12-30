#include "tile.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <format>

struct SDLState
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  int windowWidth;
  int windowHeight;
  int logicalWidth;
  int logicalHeight;
};

bool initialize(SDLState &state);
void cleanup(SDLState state);

int main(int, char **)
{
  SDLState state;
  state.windowWidth = 1600;
  state.windowHeight = 900;
  state.logicalWidth = 640;
  state.logicalHeight = 320;

  if (!initialize(state))
  {
    return 1;
  }

  // Load game assets
  SDL_Texture *tileTexture = IMG_LoadTexture(state.renderer, "data/tile.png");
  SDL_SetTextureScaleMode(tileTexture, SDL_SCALEMODE_NEAREST);

  // Game loop
  bool isRunning = true;
  SDL_Event event;
  while (isRunning)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
      {
        isRunning = false;
        break;
      }
      case SDL_EVENT_WINDOW_RESIZED:
      {
        state.windowWidth = event.window.data1;
        state.windowHeight = event.window.data2;
      }
      }
    }

    // Perform drawing commands
    SDL_SetRenderDrawColor(state.renderer, 50, 50, 50, 255);
    SDL_RenderClear(state.renderer);

    SDL_FRect src{
        .x = 0,
        .y = 0,
        .w = 16,
        .h = 16};

    SDL_FRect dst{
        .x = 0,
        .y = 0,
        .w = 32,
        .h = 32};

    SDL_RenderTexture(state.renderer, tileTexture, &src, &dst);

    SDL_RenderPresent(state.renderer);
  }

  SDL_DestroyTexture(tileTexture);
  cleanup(state);

  return 0;
}

bool initialize(SDLState &state)
{
  bool isInitializationSuccessful = true;
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  // Create the window
  state.window = SDL_CreateWindow("Hello Window", state.windowWidth, state.windowHeight, SDL_WINDOW_RESIZABLE);

  if (!state.window)
  {
    const char *error = SDL_GetError();
    std::string errorMessage = std::format("Error creating window: {}", error);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errorMessage.c_str(), nullptr);
    isInitializationSuccessful = false;
  }

  state.renderer = SDL_CreateRenderer(state.window, nullptr);
  if (!state.renderer)
  {
    const char *error = SDL_GetError();
    std::string errorMessage = std::format("Error creating renderer: {}", error);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errorMessage.c_str(), nullptr);
    isInitializationSuccessful = false;
  }

  // configure presentation
  SDL_SetRenderLogicalPresentation(state.renderer, state.logicalWidth, state.logicalHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  return isInitializationSuccessful;
}

void cleanup(SDLState state)
{
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(state.window);
  SDL_Quit();
}
