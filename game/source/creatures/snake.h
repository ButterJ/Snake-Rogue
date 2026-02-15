#pragma once

#include "creature.h"

#include "body_part.h"
#include "direction.h"
#include "food.h"
#include "player_controlled_entity.h"
#include "resource_bar.h"
#include "sprite_specification.h"
#include "stat.h"
#include "stat_modifier.h"

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

    void eat_foods(std::set<std::shared_ptr<Food>> foods);
    void on_satiation_bar_filled();

    void on_body_part_death(std::shared_ptr<Body_part> dead_body_part) override;

    void die() override;

    Resource_bar m_satiation_bar { 100 };

    // !Temporary for testing stats
    Stat attack_damage { 20.0f, 0.0f };
};
