#pragma once

#include "sprite_specification.h"

#include <SDL3/SDL_rect.h>

#include <filesystem>

/**
 * This class is used for managing a spritesheet.
 * A path to the spritesheet as well as the dimensions of the sprites in the spritesheet are needed.
 * It allows easily getting a sprite specification of a sprite in the spritesheet by its index.
 * This class can also be used for files with a single sprite.
 */
class Spritesheet
{
  public:
    Spritesheet(std::filesystem::path spritesheet_path, float sprite_width, float sprite_height);

    Sprite_specification get_sprite_specification(int index_horizontal, int index_vertical) const;

  private:
    const std::filesystem::path m_spritesheet_path;

    const float m_sprite_width;
    const float m_sprite_height;
};
