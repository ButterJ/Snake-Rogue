#pragma once

#include "game_object.h"

#include "creature_stats.h"
#include "position.h"
#include "resource_bar.h"
#include "sprite_component.h"
#include "sprite_specification.h"
#include "transform_component.h"
#include "turn_based_entity.h"

#include <memory>
#include <set>

class Food : public Game_object
{
  public:
    Food(const Position& position, const Sprite_specification& sprite_specification, int satiation);

    virtual void eat(std::shared_ptr<Turn_based_entity> turn_based_entity, Resource_bar& satiation_bar, Creature_stats& creature_stats) = 0;

  protected:
    std::shared_ptr<Transform_component> m_transform_component;
    std::shared_ptr<Sprite_component> m_sprite_component;

    int m_satiation;
};
