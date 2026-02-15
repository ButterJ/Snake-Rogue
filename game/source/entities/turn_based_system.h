#pragma once

#include "player_controlled_entity.h"
#include "turn_based_entity.h"

#include <functional>
#include <list>
#include <memory>
#include <set>

class Turn_based_system
{
  public:
    void register_entity(std::shared_ptr<Turn_based_entity> turn_based_entity);
    void release_entity(std::shared_ptr<Turn_based_entity> turn_based_entity);

    void update(float delta_time);

  private:
    enum Process_result
    {
        continue_processing,
        require_player_input
    };

    const Process_result process_entity_turns();

    Process_result tick_player_controlled_entities();
    void tick_other_entities();

    const bool is_waiting_for_input_cooldown() const;
    void on_player_turn_finished();

    std::set<std::shared_ptr<Turn_based_entity>> player_controlled_entities {};
    std::set<std::shared_ptr<Turn_based_entity>> processed_player_controlled_entities {};

    std::set<std::shared_ptr<Turn_based_entity>> other_entities {};
    std::shared_ptr<Turn_based_entity> current_player_controlled_entity {};

    bool m_is_player_turn { false };
    const float m_delay_after_input { 0.1f };
    float m_current_input_delay { 0.0f };
};
