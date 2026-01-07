#pragma once

#include "player_controlled_entity.h"
#include "turn_based_entity.h"
#include <functional>
#include <list>
#include <memory>

class Time_system
{
  public:
    enum Process_result
    {
        continue_processing,
        require_player_input
    };

    const Process_result process_entity_turns();
    void register_entity(std::weak_ptr<Turn_based_entity> turn_based_entity);
    void release_entity(std::weak_ptr<Turn_based_entity> turn_based_entity);

  private:
    void tick();
    Process_result tick_player_controlled_entities();
    void tick_other_entities();

    std::list<std::weak_ptr<Player_controlled_entity>> player_controlled_entities {};
    std::list<std::weak_ptr<Turn_based_entity>> other_entities {};
};
