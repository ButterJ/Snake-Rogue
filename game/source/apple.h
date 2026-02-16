#pragma once

#include "food.h"

#include "timed_stat_modifier.h"

#include <memory>

class Apple : public Food
{
  public:
    Apple(const Position& position, const Sprite_specification& sprite_specification, int satiation);

    void eat(std::shared_ptr<Turn_based_entity> turn_based_entity, Resource_bar& satiation_bar, Creature_stats& creature_stats) override;
};
