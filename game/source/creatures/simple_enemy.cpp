#include "simple_enemy.h"

#include "simple_enemy_input_controller.h"

Simple_enemy::Simple_enemy(int number_of_body_parts, const Sprite_specification& sprite_specification)
    : Creature(number_of_body_parts, sprite_specification, std::make_shared<Simple_enemy_input_controller>(m_body_parts))
{
}
