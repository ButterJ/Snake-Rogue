#include "sprite_component.h"

void Sprite_component::render()
{
    const Position& position { m_transform_component.get()->position };
    const SDL_FRect pixel_size { m_sprite_specification.pixel_size };
    const SDL_FRect destination_rectangle { .x = pixel_size.x * position.x, .y = pixel_size.y * position.y, .w = pixel_size.x, .h = pixel_size.y };

    SDL_RenderTexture(sdl_manager.get_state().renderer, &sdl_manager.get_texture(m_sprite_specification.texture_file_path), &m_sprite_specification.texture_source_rectangle, &destination_rectangle);
}
