#include "sprite_renderer.h"
#include "position.h"

#include <SDL3_image/SDL_image.h>

void Sprite_renderer::register_sprite_component(std::shared_ptr<Sprite_component> sprite_component)
{
    sprite_components[sprite_component.get()->get_id()] = sprite_component; // TODO: Might want to check if the element already exists
}

void Sprite_renderer::release_sprite_component(std::shared_ptr<Sprite_component> sprite_component)
{
    sprite_components.erase(sprite_component.get()->get_id()); // TODO: Might want to check if the element does not exist
}

void Sprite_renderer::render_sprites() const
{
    for (auto sprite : sprite_components)
    {
        render_sprite(sprite.second);
    }
}

void Sprite_renderer::render_sprite(std::shared_ptr<Sprite_component> sprite_component) const
{
    const Position& position { sprite_component.get()->get_transform_component().get()->position };
    const Sprite_specification sprite_specification { sprite_component.get()->get_sprite_specification() };
    const SDL_FRect destination_rectangle { .x = 12.8f * position.x, .y = 23.2f * position.y, .w = 12.8f, .h = 23.2f }; // TODO: Need to replace magic numbers

    SDL_RenderTexture(sdl_manager.get_state().renderer, &sdl_manager.get_texture(sprite_specification.texture_file_path), &sprite_specification.texture_source_rectangle, &destination_rectangle);
}
