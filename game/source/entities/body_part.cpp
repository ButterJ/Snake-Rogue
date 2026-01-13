#include "body_part.h"

#include "dungeon_layer.h"

#include <SDL3/SDL_log.h>

std::shared_ptr<Transform_component> Body_part::get_transform_component()
{
    return transform_component;
}

void Body_part::set_position(const Position& position)
{
    bool is_position_occupied { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->is_occupied(position) };

    if (is_position_occupied) // TODO: Do proper handling
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Position is occupied");
        return;
    }

    auto previous_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(transform_component.get()->position) };
    previous_tile.get()->remove_game_object(Tile::Occupant_type::body_part);
    transform_component.get()->position = position;
    auto new_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(transform_component.get()->position) };
    new_tile.get()->add_game_object(Tile::Occupant_type::body_part, shared_from_this());
}

void Body_part::move(const Direction& direction)
{
    auto move_position { transform_component.get()->position + direction };
    set_position(move_position);
}
