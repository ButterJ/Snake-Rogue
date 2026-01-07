#pragma once

#include "body_part.h"
#include "direction.h"
#include "i_player_entity.h"
#include "player_controlled_entity.h"
#include "turn_based_entity.h"
#include <list>

class Snake : public Player_controlled_entity
{
  public:
    Snake(int number_of_body_parts)
        : body_parts { Body_part { Position { 1, 1 } }, Body_part { Position { 2, 1 } }, Body_part { Position { 2, 2 } } }
    {
        current_energy = turn_energy_cost; // So that the player is first. // TODO: Might need to change this
    }

    const Input_result process_input() override;
    const std::list<Body_part>& get_body_parts() const;
    void move(const Direction& direction);

  protected:
    void take_turn() override;

  private:
    std::list<Body_part> body_parts {};
};
