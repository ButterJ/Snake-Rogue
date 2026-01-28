#pragma once

#include "creature.h"
#include "turn_based_entity.h"

class Game_controlled_creature : public Creature<Turn_based_entity>
{
  public:
    Action_result move(const Direction& direction) override;
    Action_result set_position(const Position& position) override;
    void add_body_part(std::shared_ptr<Body_part> body_part) override;

  protected:
    void on_death();
};
