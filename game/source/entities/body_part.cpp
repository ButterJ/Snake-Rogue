#include "body_part.h"

#include "colour.h"
#include "dungeon_layer.h"

#include <SDL3/SDL_log.h>

Body_part::Body_part(std::shared_ptr<Sprite_component> sprite_component, std::shared_ptr<Transform_component> transform_component)
    : m_sprite_component { sprite_component }
    , m_transform_component { transform_component }
    , m_collider_component { std::make_shared<Collider_component>() }
    , m_health_component { std::make_shared<Health_component>(100) }
{
    components.push_back(m_sprite_component);
    components.push_back(m_transform_component);
    components.push_back(m_collider_component);
    components.push_back(m_health_component);

    m_health_component.get()->On_death_callback.append([this]()
                                                       { on_death(); });
}

std::shared_ptr<Transform_component> Body_part::get_transform_component()
{
    return m_transform_component;
}

Action_result Body_part::set_position(const Position& position)
{
    auto current_floor { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor() };
    bool is_position_occupied { current_floor->is_tile_occupied(position) };

    if (is_position_occupied)
    {
        return Action_result::failure;
    }

    auto previous_tile { current_floor->get_tile_at_position(get_position()) };
    previous_tile.get()->remove_game_object(Tile::Occupant_type::body_part); // TODO: I don't like that the body part knows of the tile like this
    m_transform_component.get()->position = position;
    auto new_tile { current_floor->get_tile_at_position(get_position()) };
    new_tile.get()->add_game_object(Tile::Occupant_type::body_part, shared_from_this());

    return Action_result::success;
}

Action_result Body_part::move(const Direction& direction)
{
    auto move_position { m_transform_component.get()->position + direction };
    return set_position(move_position);
}

const Position& Body_part::get_position() const
{
    return m_transform_component->position;
}

void Body_part::change_health(int health_change)
{
    m_health_component->change_health(health_change);

    double health_percentage { static_cast<double>(m_health_component->get_health()) / m_health_component->get_max_health() };
    m_sprite_component->set_colour({ 255, static_cast<uint8_t>(health_percentage * 255), static_cast<uint8_t>(health_percentage * 255), 255 });
}

void Body_part::die()
{
    on_death();
}

void Body_part::on_death()
{
    On_death_callback();
    auto current_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(get_position()) };
    current_tile->remove_game_object(Tile::Occupant_type::body_part);
}
