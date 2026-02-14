#include "tile.h"

#include "collider_component.h"

#include <SDL3/SDL_log.h>

#include <assert.h>

bool Tile::is_occupied() const
{
    if (is_occupied_by_type(Occupant_type::body_part))
    {
        return true;
    }

    if (is_occupied_by_type(Occupant_type::environment_object))
    {
        return true;
    }

    return false;
}

bool Tile::is_occupied_by_type(Occupant_type occupant_type) const
{
    auto occupant_pair { m_held_game_objects.find(occupant_type) };

    if (occupant_pair != m_held_game_objects.end())
    {
        for (auto occupant : occupant_pair->second)
        {
            if (occupant->get_component<Collider_component>())
            {
                return true;
            }
        }
    }

    return false;
}

void Tile::add_game_object(Occupant_type tile_occupant_type, std::shared_ptr<Game_object> game_object)
{
    if (!m_held_game_objects.contains(tile_occupant_type))
    {
        m_held_game_objects.insert({ tile_occupant_type, std::set<std::shared_ptr<Game_object>> { game_object } });
        return;
    }

    auto game_objects_of_type { m_held_game_objects.find(tile_occupant_type) };
    game_objects_of_type->second.insert(game_object);
}

void Tile::remove_game_object(Occupant_type tile_occupant_type)
{
    auto game_objects_of_type { m_held_game_objects.find(tile_occupant_type) };

    if (game_objects_of_type != m_held_game_objects.end())
    {
        game_objects_of_type->second.clear();
    }
}

void Tile::render() const
{
    if (render_occupant_type(Occupant_type::body_part))
    {
        return;
    }

    if (render_occupant_type(Occupant_type::food))
    {
        return;
    }

    if (render_occupant_type(Occupant_type::environment_object))
    {
        return;
    }
}

bool Tile::render_occupant_type(Occupant_type occupant_type) const
{
    auto occupant_pair { m_held_game_objects.find(occupant_type) };

    if (occupant_pair != m_held_game_objects.end())
    {
        for (auto occupant : occupant_pair->second)
        {
            auto sprite_component { occupant->get_component<Sprite_component>() };
            if (sprite_component)
            {
                sprite_component->get()->render();
                return true;
            }
        }
    }

    return false;
}

std::shared_ptr<Body_part> Tile::get_held_body_part() const
{
    auto body_parts_pair { m_held_game_objects.find(Occupant_type::body_part) };

    if (body_parts_pair != m_held_game_objects.end())
    {
        if (body_parts_pair->second.size() == 0)
        {
            return nullptr;
        }

        auto game_object { *body_parts_pair->second.begin() };
        auto body_part { std::dynamic_pointer_cast<Body_part>(game_object) };
        return body_part;
    }

    return nullptr;
}

std::set<std::shared_ptr<Food>> Tile::get_held_foods() const
{
    auto foods_pair { m_held_game_objects.find(Occupant_type::food) };

    if (foods_pair != m_held_game_objects.end())
    {
        auto game_objects { foods_pair->second };

        std::set<std::shared_ptr<Food>> foods {};
        for (auto game_object : game_objects)
        {
            auto food { std::dynamic_pointer_cast<Food>(game_object) };
            foods.insert(food);
        }

        return foods;
    }

    return std::set<std::shared_ptr<Food>> {};
}
