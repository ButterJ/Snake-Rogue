#pragma once

#include "creature.h"
#include "player_controlled_entity.h"

class Player_controlled_creature : public Creature<Player_controlled_entity>
{
  public:
    void add_body_part(std::shared_ptr<Body_part> body_part) override;
    void render() override;

  protected:
    void take_turn() override;
};
