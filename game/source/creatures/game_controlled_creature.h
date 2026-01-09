#pragma once

#include "creature.h"
#include "turn_based_entity.h"

class Game_controlled_creature : public Creature<Turn_based_entity>
{
  public:
    void move(const Direction& direction) override;
    void add_body_part(std::shared_ptr<Body_part> body_part) override;
    void render() override;
};
