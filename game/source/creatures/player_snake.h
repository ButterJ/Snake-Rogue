#pragma once

#include "creature.h"

#include "player_input_controller.h"

class Player_snake : public Creature
{
  public:
    Player_snake(int number_of_body_parts);

  protected:
    void die() override;

  private:
    static Sprite_specification create_sprite_specification();
    static std::shared_ptr<Player_input_controller> create_input_controller();
};
