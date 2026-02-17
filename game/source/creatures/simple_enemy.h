#pragma once

#include "creature.h"

#include "simple_enemy_input_controller.h"

#include <memory>

class Simple_enemy : public Creature
{
  public:
    Simple_enemy(int number_of_body_parts);

  private:
    static Sprite_specification create_sprite_specification();
    static std::shared_ptr<Simple_enemy_input_controller> create_input_controller(std::vector<std::shared_ptr<Body_part>>& body_parts);
};
