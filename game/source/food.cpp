#include "food.h"

Food::Food(const Position& position, const Sprite_specification& sprite_specification, int satiation)
    : m_transform_component { std::make_shared<Transform_component>(position) }
    , m_sprite_component { std::make_shared<Sprite_component>(sprite_specification, m_transform_component) }
    , m_satiation { satiation }
{
    components.push_back(m_transform_component);
    components.push_back(m_sprite_component);
}

void Food::eat(std::shared_ptr<Turn_based_entity> turn_based_entity, Resource_bar& satiation_bar, Creature_stats& creature_stats)
{
    satiation_bar.change_value(m_satiation);
}
