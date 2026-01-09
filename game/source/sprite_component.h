#pragma once

#include "component.h"
#include "position.h"
#include "sprite_specification.h"
#include "transform_component.h"

#include <memory>
#include <string>

class Sprite_component : public Component
{
  public:
    Sprite_component(Sprite_specification p_sprite_specification, std::shared_ptr<Transform_component> p_transform_component);
    // ~Sprite_component();

    const Sprite_specification& get_sprite_specification() const;
    const std::shared_ptr<const Transform_component> get_transform_component() const;

  private:
    Sprite_specification sprite_specification;
    std::shared_ptr<Transform_component> transform_component;
    // Sprite_renderer& sprite_renderer;
};
