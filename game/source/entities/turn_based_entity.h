#pragma once

#include "action_result.h"
#include "input_action.h"
#include "input_controller.h"

#include "eventpp/callbacklist.h"

#include <memory>

class Turn_based_entity : public std::enable_shared_from_this<Turn_based_entity>
{
  public:
    enum Tick_result
    {
        none,
        taking_turn
    };

    // TODO: Also need to be able to give energy parameters to constructor
    Turn_based_entity(std::shared_ptr<Input_controller> input_controller);

    Tick_result tick();

    bool is_player_controlled() const;
    void try_processing_player_input();

    eventpp::CallbackList<void()> On_turn_finished_callback {};
    eventpp::CallbackList<void()> On_death_callback {};

  protected:
    void start_turn(); // TODO: Make return type that gives information whether the turn got finished immediately?
    virtual void on_turn_finished();

    virtual Action_result perform_input_action(std::shared_ptr<Input_action> input_action) = 0;

    virtual void die();

    int m_turn_energy_cost { 100 };
    int m_energy_regeneration { 20 };
    int m_current_energy { 0 };

    std::shared_ptr<Input_controller> m_input_controller {};
};
