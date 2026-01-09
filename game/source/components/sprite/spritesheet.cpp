#include "spritesheet.h"

Sprite_specification Spritesheet::get_sprite_specification(int index_horizontal, int index_vertical) const
{
    SDL_FRect source_rectangle {
        .x { sprite_width * index_horizontal },
        .y { sprite_height * index_vertical },
        .w { sprite_width },
        .h { sprite_height }
    };
    return { .texture_file_path { spritesheet_path }, .texture_source_rectangle { source_rectangle } };
}
