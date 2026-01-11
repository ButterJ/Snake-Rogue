#include "body_part.h"

#include "dungeon_layer.h"

#include <SDL3/SDL_log.h>

std::shared_ptr<Transform_component> Body_part::get_transform_component()
{
    return transform_component;
}

void Body_part::move(const Direction& direction)
{
    auto move_position { transform_component.get()->position + direction };
    auto is_move_position_occupied { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->is_occupied(move_position) };

    if (is_move_position_occupied) // TODO: Do proper handling
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Move direction occupied");
        return;
    }

    // auto previous_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(transform_component.get()->position) };
    // previous_tile.get()->remove_game_object(this);
    transform_component.get()->position += direction;
    // auto new_tile { Core::Game::get_instance().get_layer<Dungeon_layer>()->get_current_floor()->get_tile_at_position(transform_component.get()->position) };
    // new_tile.get()->add_game_object(this);
}

void Body_part::render()
{
    sprite_component.get()->render();
}
