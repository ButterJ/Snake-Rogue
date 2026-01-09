#include "sprite_component.h"

Sprite_component::Sprite_component(Sprite_specification p_sprite_specification, std::shared_ptr<Transform_component> p_transform_component)
    : sprite_specification { p_sprite_specification }, transform_component { p_transform_component }
{
    // sprite_renderer.register_sprite_component(std::make_shared<Sprite_component>(this));
}

// Sprite_component::~Sprite_component()
// {
//     sprite_renderer.release_sprite_component(std::make_shared<Sprite_component>(this));
// }

const Sprite_specification& Sprite_component::get_sprite_specification() const
{
    return sprite_specification;
}

const std::shared_ptr<const Transform_component> Sprite_component::get_transform_component() const
{
    return transform_component;
}
