#pragma once

#include "position.h"
#include "turn_based_entity.h"

class Enemy : public Turn_based_entity
{
  protected:
    void take_turn() override;
};
