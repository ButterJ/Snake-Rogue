#include "apple.h"

Apple::Apple(const Position& position, const Sprite_specification& sprite_specification, int satiation)
    : Food(position, sprite_specification, satiation)
{
}

void Apple::eat(std::shared_ptr<Turn_based_entity> turn_based_entity, Resource_bar& satiation_bar, Creature_stats& creature_stats)
{
    satiation_bar.change_value(m_satiation);

    auto& health_regeneration_stat { creature_stats.health_regeneration };
    auto health_regeneration_modifier { std::make_shared<Timed_stat_modifier>(Stat_modifier::Type::flat, 5.0, 3, turn_based_entity) };
    health_regeneration_stat.apply_modifier(health_regeneration_modifier);
}
