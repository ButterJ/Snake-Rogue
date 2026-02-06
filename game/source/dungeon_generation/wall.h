#pragma once

#include "environment_object.h"

#include "collider_component.h"
#include "position.h"
#include "spritesheet.h"

class Wall : public Environment_object
{
  public:
    Wall(const Position& position) : Environment_object(position), m_collider_component { std::make_shared<Collider_component>() }
    {
        Spritesheet spritesheet { "data/tiles.png", 128.0f, 232.0f };
        Sprite_specification sprite_specification { spritesheet.get_sprite_specification(3, 2) };

        m_sprite_component = std::make_shared<Sprite_component>(sprite_specification, m_transform_component);
        components.push_back(m_sprite_component);
        components.push_back(m_collider_component);
    }

  protected:
    std::shared_ptr<Sprite_component> m_sprite_component {};
    std::shared_ptr<Collider_component> m_collider_component {};
};
