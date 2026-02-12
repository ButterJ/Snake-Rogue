#pragma once

#include "environment_object.h"

#include "collider_component.h"
#include "position.h"
#include "spritesheet.h"

class Wall : public Environment_object
{
  public:
    Wall(const Position& position);

  protected:
    std::shared_ptr<Sprite_component> m_sprite_component {};
    std::shared_ptr<Collider_component> m_collider_component {};
};
