#pragma once

#include "creature.h"

class Player_snake : public Creature
{
  public:
    Player_snake(int number_of_body_parts, const Sprite_specification& sprite_specification);

  protected:
    void die() override;
};
