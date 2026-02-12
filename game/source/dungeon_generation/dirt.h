#pragma once

#include "environment_object.h"

#include "position.h"
#include "spritesheet.h"

class Dirt : public Environment_object
{
  public:
    Dirt(const Position& position);

  protected:
    std::shared_ptr<Sprite_component> m_sprite_component {};
};
