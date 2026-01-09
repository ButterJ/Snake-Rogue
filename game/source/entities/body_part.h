#pragma once

#include "direction.h"
#include "position.h"
#include "sprite_component.h"
#include "transform_component.h"
#include <memory>

class Body_part
{
  public:
    // Body_part(Position p_position)
    //     : position { p_position }
    // {
    // }

    // Body_part() = default;
    Body_part(std::shared_ptr<Sprite_component> p_sprite_component, std::shared_ptr<Transform_component> p_transform_component)
        : sprite_component { p_sprite_component }, transform_component { p_transform_component }
    {
    }

    void move(const Direction& direction);

    void render();

    std::shared_ptr<Transform_component> get_transform_component();

  private:
    std::shared_ptr<Sprite_component> sprite_component;
    std::shared_ptr<Transform_component> transform_component;
};
