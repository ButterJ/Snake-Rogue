#pragma once

#include "creature_builder.h"
#include "sprite_component.h"
#include "transform_component.h"

template <typename T_creature>
void Creature_builder<T_creature>::create_creature(int number_of_body_parts)
{
    for (int i = 0; i < number_of_body_parts; i++)
    {
        std::shared_ptr<Body_part> body_part { create_body_part() };
        creature.get()->add_body_part(body_part);
    }
}

template <typename T_creature>
std::shared_ptr<Body_part> Creature_builder<T_creature>::create_body_part()
{
    auto transform_component = std::make_shared<Transform_component>();

    Sprite_specification sprite_specification { brogue_tiles.get_sprite_specification(0, 4) };
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    auto body_part = std::make_shared<Body_part>(sprite_component, transform_component);

    return body_part;
}

template <typename T_creature>
std::shared_ptr<T_creature> Creature_builder<T_creature>::get_creature() const
{
    return creature;
}
