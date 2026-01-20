#include "body_part.h"

#include "dungeon_layer.h"

#include <SDL3/SDL_log.h>

std::shared_ptr<Transform_component> Body_part::get_transform_component()
{
    return m_transform_component;
}

Action_result Body_part::set_position(const Position& position)
{
    bool is_position_occupied { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->is_occupied(position) };

    if (is_position_occupied)
    {
        return Action_result::failure;
    }

    auto previous_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(get_position()) };
    previous_tile.get()->remove_game_object(Tile::Occupant_type::body_part);
    m_transform_component.get()->position = position;
    auto new_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(get_position()) };
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
}

void Body_part::on_death()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Health component died");
    On_death_callback();
    // auto current_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(get_position()) };
    // current_tile->remove_game_object(Tile::Occupant_type::body_part);
}
