#pragma once

#include "collider_component.h"
#include "direction.h"
#include "game_object.h"
#include "i_renderable.h"
#include "position.h"
#include "sprite_component.h"
#include "transform_component.h"

#include <memory>

class Body_part : public Game_object, public I_renderable
{
  public:
    Body_part(std::shared_ptr<Sprite_component> p_sprite_component, std::shared_ptr<Transform_component> p_transform_component)
        : sprite_component { p_sprite_component }, transform_component { p_transform_component }, collider_component { std::make_shared<Collider_component>() }
    {
        components.push_back(sprite_component);
        components.push_back(transform_component);
        components.push_back(collider_component);
    }

    void set_position(const Position& position);
    void move(const Direction& direction);

    void render() override;

    std::shared_ptr<Transform_component> get_transform_component();

  private:
    std::shared_ptr<Sprite_component> sprite_component;
    std::shared_ptr<Transform_component> transform_component;
    std::shared_ptr<Collider_component> collider_component;
};
