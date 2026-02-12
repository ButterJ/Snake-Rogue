#pragma once

#include "eventpp/callbacklist.h"

class Turn_based_entity
{
  public:
    enum Tick_result
    {
        none,
        taking_turn
    };

    Tick_result tick();

    eventpp::CallbackList<void()> On_death_callback {};

  protected:
    virtual void take_turn() = 0;

    virtual void die();

    int m_turn_energy_cost { 100 };
    int m_energy_regeneration { 20 };
    int m_current_energy { 0 };
};
