#pragma once

#include "sprite_specification.h"

#include <SDL3/SDL_rect.h>

#include <filesystem>

class Spritesheet // TODO: Add description to this class, it is not fully clear
{
  public:
    Spritesheet(std::filesystem::path spritesheet_path, float sprite_width, float sprite_height);

    Sprite_specification get_sprite_specification(int index_horizontal, int index_vertical) const;

  private:
    const std::filesystem::path m_spritesheet_path;

    const float m_sprite_width;
    const float m_sprite_height;
};
