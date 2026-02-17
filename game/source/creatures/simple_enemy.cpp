#include "simple_enemy.h"

#include "spritesheet.h"

Simple_enemy::Simple_enemy(int number_of_body_parts)
    : Creature(number_of_body_parts, create_sprite_specification(), create_input_controller(m_body_parts))
{
}

Sprite_specification Simple_enemy::create_sprite_specification()
{
    static Spritesheet spritesheet { "data/body_part_enemy.png", 16.0f, 16.0f };
    return spritesheet.get_sprite_specification(0, 0);
}

std::shared_ptr<Simple_enemy_input_controller> Simple_enemy::create_input_controller(std::vector<std::shared_ptr<Body_part>>& body_parts)
{
    return std::make_shared<Simple_enemy_input_controller>(body_parts);
}
