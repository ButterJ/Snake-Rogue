#pragma once

#include "sprite_component.h"
#include "sprite_specification.h"

#include <SDL3/SDL_rect.h>

#include <filesystem>

class Spritesheet // TODO: Add description to this class, it is not fully clear
{
  public:
    Spritesheet(std::filesystem::path p_spritesheet_path, float p_sprite_width, float p_sprite_height)
        : spritesheet_path { p_spritesheet_path }, sprite_width { p_sprite_width }, sprite_height { p_sprite_height }
    {
    }

    Sprite_specification get_sprite_specification(int index_horizontal, int index_vertical) const;

  private:
    const std::filesystem::path spritesheet_path;
    const float sprite_width;
    const float sprite_height;
};
