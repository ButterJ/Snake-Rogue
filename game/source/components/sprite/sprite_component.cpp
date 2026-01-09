#include "sprite_component.h"

Sprite_component::Sprite_component(Sprite_specification p_sprite_specification, std::shared_ptr<Transform_component> p_transform_component)
    : sprite_specification { p_sprite_specification }, transform_component { p_transform_component }
{
    // sprite_renderer.register_sprite_component(std::make_shared<Sprite_component>(this));
}

void Sprite_component::render()
{
    const Position& position { transform_component.get()->position };
    const SDL_FRect destination_rectangle { .x = 12.8f * position.x, .y = 23.2f * position.y, .w = 12.8f, .h = 23.2f }; // TODO: Need to replace magic numbers

    SDL_RenderTexture(sdl_manager.get_state().renderer, &sdl_manager.get_texture(sprite_specification.texture_file_path), &sprite_specification.texture_source_rectangle, &destination_rectangle);
}
