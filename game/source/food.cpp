#include "food.h"

Food::Food(const Position& position, const Sprite_specification& sprite_specification, int satiation)
    : m_transform_component { std::make_shared<Transform_component>(position) }
    , m_sprite_component { std::make_shared<Sprite_component>(sprite_specification, m_transform_component) }
    , m_satiation { satiation }
{
    components.push_back(m_transform_component);
    components.push_back(m_sprite_component);
}
