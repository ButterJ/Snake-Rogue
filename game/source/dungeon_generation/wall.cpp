#include "wall.h"

Wall::Wall(const Position& position)
    : Environment_object(position)
    , m_collider_component { std::make_shared<Collider_component>() }
{
    Spritesheet spritesheet { "data/hashtag_01.png", 16.0f, 16.0f };
    Sprite_specification sprite_specification { spritesheet.get_sprite_specification(0, 0) };

    m_sprite_component = std::make_shared<Sprite_component>(sprite_specification, m_transform_component);
    components.push_back(m_sprite_component);
    components.push_back(m_collider_component);
}
