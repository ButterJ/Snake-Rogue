#pragma once

#include "body_part.h"
#include "creature.h"
#include "game_controlled_creature.h"
#include "position.h"
#include "sprite_component.h"
#include "sprite_specification.h"
#include "transform_component.h"

#include <memory>

class Enemy : public Game_controlled_creature // TODO: Right now this is a class to test out enemies in the game. Should probably be named Monster or Creature and be a base clas
{
  public:
    void take_turn() override;
};
