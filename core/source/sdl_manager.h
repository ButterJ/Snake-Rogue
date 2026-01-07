#pragma once

#include <SDL3/SDL.h>

namespace Core
{

class Sdl_manager
{
  public:
    struct Window_specification
    {
        const char* window_name { "Snake Rogue" };
        int window_width { 1600 };
        int window_height { 900 };
        int logical_width { 640 };
        int logical_height { 320 };
    };

    struct State
    {
        SDL_Window* window {};
        SDL_Renderer* renderer {};
        Window_specification window_specification {};
    };

    void initialize();
    const SDL_AppResult handle_event(const SDL_Event* const event);
    void cleanup();

    const State& get_state() const;

  private:
    void create_window_and_renderer();
    void set_window_dimensions(int windowWidth, int windowHeight);

    State state {};
};

} // namespace Core
