#pragma once

#include "creature.h"

class Simple_enemy : public Creature
{
  public:
    Simple_enemy(int number_of_body_parts, const Sprite_specification& sprite_specification);
};
