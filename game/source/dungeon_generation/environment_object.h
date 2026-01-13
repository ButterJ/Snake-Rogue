#pragma once

#include "collider_component.h"
#include "game_object.h"
#include "sprite_component.h"
#include "transform_component.h"

class Environment_object : public Game_object
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
        components.push_back(transform_component);
        components.push_back(sprite_component);

        if (type == Type::wall) // TODO: Needs to be replaced
        {
            components.push_back(std::make_shared<Collider_component>());
        }
    }

  private:
    Type type {};

    std::shared_ptr<Transform_component> transform_component;
    std::shared_ptr<Sprite_component> sprite_component;
};
