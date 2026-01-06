#pragma once

#include "turn_based_entity.h"
#include <functional>
#include <list>
#include <memory>

class Time_system
{
  public:
    void tick();
    void register_entity(std::weak_ptr<Turn_based_entity> turn_based_entity);
    void release_entity(std::weak_ptr<Turn_based_entity> turn_based_entity);

  private:
    std::list<std::weak_ptr<Turn_based_entity>> player_entities {};
    std::list<std::weak_ptr<Turn_based_entity>> other_entities {};
};
