#pragma once

#include "turn_based_entity.h"

class Player_controlled_entity : public Turn_based_entity
{
  public:
    enum Input_result
    {
        none,
        turn_finished,
        invalid_action
    };

    virtual const Input_result process_input() = 0;

    bool is_processed { false };
};
