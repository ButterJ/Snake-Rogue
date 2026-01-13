#pragma once

#include "body_part.h"
#include "creature.h"
#include "direction.h"
#include "i_player_entity.h"
#include "player_controlled_creature.h"
#include "sprite_component.h"
#include "sprite_specification.h"
#include "turn_based_entity.h"

#include <list>
#include <memory>

class Snake : public Player_controlled_creature
{
  public:
    const Input_result process_input() override;

    Action_result set_position(const Position& position) override;
    Action_result move(const Direction& direction) override;
};
