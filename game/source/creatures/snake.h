#pragma once

#include "creature.h"

#include "body_part.h"
#include "direction.h"
#include "food.h"
#include "i_player_entity.h"
#include "player_controlled_entity.h"
#include "resource_bar.h"
#include "sprite_component.h"
#include "sprite_specification.h"
#include "turn_based_entity.h"

#include <list>
#include <memory>
#include <set>

class Snake : public Creature<Player_controlled_entity>
{
  public:
    Snake(int number_of_body_parts, const Sprite_specification& sprite_specification);

    const Input_result process_input() override;

    Action_result set_position(const Position& position) override;
    Action_result move(const Direction& direction) override;

  private:
    Input_result on_direction_input(const Direction& direction);
    Action_result attack(const Direction& direction);
    void on_body_part_death(std::shared_ptr<Body_part> dead_body_part) override;
    void eat_foods(std::set<std::shared_ptr<Food>> foods);
    void on_satiation_bar_filled();

  protected:
    void take_turn() override;
    void die() override;

    Resource_bar satiation_bar { 100 };
};
