#pragma once

#include "creature.h"

#include "body_part.h"
#include "position.h"
#include "sprite_specification.h"
#include "turn_based_entity.h"

#include <memory>
#include <vector>

// TODO: Right now this is a class is for testing out the single enemy type in the prototype. Should be named Monster and be a base clas
class Enemy : public Creature<Turn_based_entity>
{
  public:
    Enemy(int number_of_body_parts, const Sprite_specification& sprite_specification);

    Action_result move(const Direction& direction) override;
    Action_result set_position(const Position& position) override;

    void take_turn() override;

    Action_result attack_adjacent_target(const std::vector<std::shared_ptr<Body_part>>& targets);

  protected:
    void on_body_part_death(std::shared_ptr<Body_part> dead_body_part) override;
    void die() override;

  private:
    Action_result move_towards_weighted_random_direction(const std::vector<Direction>& occupied_directions);

    Direction m_last_move_direction {};
};
