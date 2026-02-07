#pragma once

#include "environment_object.h"

#include "position.h"
#include "spritesheet.h"

class Dirt : public Environment_object
{
  public:
    Dirt(const Position& position) : Environment_object(position)
    {
        Spritesheet spritesheet { "data/dirt.png", 16.0f, 16.0f };
        Sprite_specification sprite_specification { spritesheet.get_sprite_specification(0, 0) };

        m_sprite_component = std::make_shared<Sprite_component>(sprite_specification, m_transform_component);
        components.push_back(m_sprite_component);
    }

  protected:
    std::shared_ptr<Sprite_component> m_sprite_component {};
};
