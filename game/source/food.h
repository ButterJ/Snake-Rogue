#pragma once

#include "game_object.h"
#include "position.h"
#include "sprite_component.h"
#include "sprite_specification.h"
#include "transform_component.h"

class Food : public Game_object
{
  public:
    Food(const Position& position, const Sprite_specification& sprite_specification, int satiation);

    int get_satiation_value() { return m_satiation; }

  protected:
    std::shared_ptr<Transform_component> m_transform_component;
    std::shared_ptr<Sprite_component> m_sprite_component;

    int m_satiation;
};
