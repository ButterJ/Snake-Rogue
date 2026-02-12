#include "sprite_component.h"

Sprite_component::Sprite_component(Sprite_specification sprite_specification, std::shared_ptr<Transform_component> transform_component)
    : m_sprite_specification { sprite_specification }
    , m_transform_component { transform_component }
{
}

void Sprite_component::render()
{
    const Position& position { m_transform_component.get()->position };
    const SDL_FRect pixel_size { m_sprite_specification.pixel_size };
    const SDL_FRect destination_rectangle { .x = pixel_size.x * position.x, .y = pixel_size.y * position.y, .w = pixel_size.x, .h = pixel_size.y };

    SDL_Texture& texture { m_sdl_manager.get_texture(m_sprite_specification.texture_file_path) };
    SDL_SetTextureColorMod(&texture, m_colour.r, m_colour.g, m_colour.b);
    SDL_RenderTexture(m_sdl_manager.get_state().renderer, &texture, &m_sprite_specification.texture_source_rectangle, &destination_rectangle);
}

void Sprite_component::set_colour(Colour colour)
{
    m_colour = colour;
}
