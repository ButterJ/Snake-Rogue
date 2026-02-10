#pragma once

#include "body_part.h"
#include "creature.h"
#include "position.h"
#include "sprite_component.h"
#include "sprite_specification.h"
#include "transform_component.h"
#include "turn_based_entity.h"

#include <memory>
#include <set>
#include <vector>

class Enemy : public Creature<Turn_based_entity> // TODO: Right now this is a class to test out enemies in the game. Should probably be named Monster or Creature and be a base clas
{
  public:
    Action_result move(const Direction& direction) override;
    Action_result set_position(const Position& position) override;
    Action_result attack_adjacent_target(const std::vector<std::shared_ptr<Body_part>>& targets);

    void add_body_part(std::shared_ptr<Body_part> body_part) override;

  protected:
    void on_death();

  public:
    void take_turn() override;

  private:
    Action_result move_towards_weighted_random_direction(const std::vector<Direction>& occupied_directions);
    Direction last_move_direction {};
};
