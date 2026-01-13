#include "tile.h"
#include "collider_component.h"
#include "environment_object.h"
#include <assert.h>

bool Tile::is_occupied() const
{
    if (held_body_part)
    {
        if (held_body_part.get()->get_component<Collider_component>())
        {
            return true;
        }
    }

    if (held_environment_object)
    {
        if (held_environment_object.get()->get_component<Collider_component>())
        {
            return true;
        }
    }

    return false;
}

void Tile::add_game_object(Occupant_type tile_occupant_type, std::shared_ptr<Game_object> game_object)
{
    switch (tile_occupant_type)
    {
        case environment_object:
            // assert(!held_environment_object && "Tile already has an environment object");
            held_environment_object = game_object;
            break;
        case body_part:
            // assert(!held_body_part && "Tile already has a body part");
            held_body_part = game_object;
            break;
    }
}

void Tile::remove_game_object(Occupant_type Tile_occupant_type)
{
    switch (Tile_occupant_type)
    {
        case environment_object:
            // assert(held_environment_object && "Tile has no environment object to remove");
            held_environment_object = nullptr;
            break;
        case body_part:
            // assert(held_body_part && "Tile has no body part to remove");
            held_body_part = nullptr;
            break;
    }
}

void Tile::render() const
{
    if (held_body_part)
    {
        auto sprite_component { held_body_part.get()->get_component<Sprite_component>() };

        if (sprite_component)
        {
            sprite_component->get()->render();
            return;
        }
    }

    if (held_environment_object)
    {
        auto sprite_component { held_environment_object.get()->get_component<Sprite_component>() };

        if (sprite_component)
        {
            sprite_component->get()->render();
            return;
        }
    }
}
