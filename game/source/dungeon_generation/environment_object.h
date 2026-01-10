#pragma once

#include "i_renderable.h"
#include "sprite_component.h"
#include "transform_component.h"

class Environment_object : public I_renderable
{
  public:
    enum class Type
    {
        none,
        wall,
        floor,
    };

    Environment_object(Type p_type, std::shared_ptr<Transform_component> p_transform_component, std::shared_ptr<Sprite_component> p_sprite_component)
        : type { p_type }, transform_component { p_transform_component }, sprite_component { p_sprite_component }
    {
    }

    void render() override;

  private:
    Type type {};

    std::shared_ptr<Transform_component> transform_component;
    std::shared_ptr<Sprite_component> sprite_component;
};
