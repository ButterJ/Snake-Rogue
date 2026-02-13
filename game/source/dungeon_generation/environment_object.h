#pragma once

#include "game_object.h"

#include "position.h"
#include "sprite_component.h"
#include "transform_component.h"

class Environment_object : public Game_object
{
  public:
    Environment_object(const Position& position);
    virtual ~Environment_object() = 0;

  protected:
    std::shared_ptr<Transform_component> m_transform_component;
    std::shared_ptr<Sprite_component> m_sprite_component;
};
