#pragma once

#include "turn_based_entity.h"

#include "body_part.h"
#include "direction.h"
#include "food.h"
#include "position.h"
#include "resource_bar.h"
#include "sprite_specification.h"
#include "stat.h"

#include <concepts>
#include <list>
#include <memory>
#include <set>

class Creature : public Turn_based_entity
{
  public:
    Creature(int number_of_body_parts, const Sprite_specification& sprite_specification);

    Action_result set_position(const Position& position);
    // Action_result move(const Direction& direction);

    Position get_head_position() const;

  protected:
    std::shared_ptr<Body_part> create_body_part();
    void add_body_part(std::shared_ptr<Body_part> body_part);

    virtual void on_body_part_death(std::shared_ptr<Body_part> dead_body_part);

    void perform_input_action(std::shared_ptr<Input_action> input_action) override;
    Action_result on_direction_input(const Direction& direction);

    Action_result attack(const Direction& direction);
    Action_result move(const Direction& direction);
    void eat_foods(std::set<std::shared_ptr<Food>> foods);

    std::list<std::shared_ptr<Body_part>> m_body_parts {};
    int m_max_body_parts { 3 };

    Sprite_specification m_sprite_specification;
    Position m_last_position {};

    Resource_bar m_satiation_bar { 100 };

    // !Temporary for testing stats
    Stat attack_damage { 20.0f, 0.0f };
};
