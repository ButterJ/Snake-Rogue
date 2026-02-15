#include "dirt.h"

Dirt::Dirt(const Position& position)
    : Environment_object(position)
{
    Spritesheet spritesheet { "data/dirt.png", 16.0f, 16.0f };
    Sprite_specification sprite_specification { spritesheet.get_sprite_specification(0, 0) };

    components.emplace_back(std::make_shared<Sprite_component>(sprite_specification, m_transform_component));
}
