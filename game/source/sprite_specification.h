#pragma once

#include <SDL3_image/SDL_image.h>

#include <filesystem>

struct Sprite_specification
{
    std::filesystem::path texture_file_path {};
    SDL_FRect texture_source_rectangle {};
};
