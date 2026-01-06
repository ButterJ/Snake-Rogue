#pragma once

class Turn_based_entity
{
  public:
    enum Tick_result
    {
        none,
        taking_turn
    };

    Tick_result tick();

  protected:
    virtual void take_turn() = 0;

    int turn_energy_cost { 100 };
    int energy_regeneration { 20 }; // Energy restored per tick
    int current_energy { 0 };
};
