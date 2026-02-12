#include "spritesheet.h"

Spritesheet::Spritesheet(std::filesystem::path spritesheet_path, float sprite_width, float sprite_height)
    : m_spritesheet_path { spritesheet_path }
    , m_sprite_width { sprite_width }
    , m_sprite_height { sprite_height }
{
}

Sprite_specification Spritesheet::get_sprite_specification(int index_horizontal, int index_vertical) const
{
    SDL_FRect source_rectangle {
        .x { m_sprite_width * index_horizontal },
        .y { m_sprite_height * index_vertical },
        .w { m_sprite_width },
        .h { m_sprite_height }
    };
    return { .texture_file_path { m_spritesheet_path }, .texture_source_rectangle { source_rectangle } };
}
