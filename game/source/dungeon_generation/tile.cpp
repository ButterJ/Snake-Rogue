#include "tile.h"

#include "collider_component.h"

#include <SDL3/SDL_log.h>

#include <assert.h>

bool Tile::is_occupied() const
{
    if (m_held_body_part)
    {
        if (m_held_body_part.get()->get_component<Collider_component>())
        {
            return true;
        }
    }

    if (m_held_environment_object)
    {
        if (m_held_environment_object.get()->get_component<Collider_component>())
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
            m_held_environment_object = game_object;
            break;
        case body_part:
            // assert(!held_body_part && "Tile already has a body part");
            auto cast_body_part { dynamic_pointer_cast<Body_part>(game_object) };

            if (!cast_body_part)
            {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot cast the given game object to a body part!");
                return;
            }

            m_held_body_part = cast_body_part;
            break;
    }
}

void Tile::remove_game_object(Occupant_type Tile_occupant_type)
{
    switch (Tile_occupant_type)
    {
        case environment_object:
            // assert(held_environment_object && "Tile has no environment object to remove");
            m_held_environment_object = nullptr;
            break;
        case body_part:
            // assert(held_body_part && "Tile has no body part to remove");
            m_held_body_part = nullptr;
            break;
    }
}

void Tile::add_food(std::shared_ptr<Food> food)
{
    m_held_foods.insert(food);
}

void Tile::remove_food(std::shared_ptr<Food> food)
{
    auto food_iterator = m_held_foods.find(food);

    if (food_iterator == m_held_foods.end())
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Could not remove food as it is not held by this tile");
        return;
    }

    m_held_foods.erase(food_iterator);
}

void Tile::remove_all_foods()
{
    m_held_foods.clear();
}

void Tile::render() const
{
    if (m_held_body_part)
    {
        auto sprite_component { m_held_body_part.get()->get_component<Sprite_component>() };

        if (sprite_component)
        {
            sprite_component->get()->render();
            return;
        }
    }

    if (m_held_foods.size() != 0)
    {
        auto topmost_food { m_held_foods.rbegin() };
        auto sprite_component { topmost_food->get()->get_component<Sprite_component>() };

        if (sprite_component)
        {
            sprite_component->get()->render();
            return;
        }
    }

    if (m_held_environment_object)
    {
        auto sprite_component { m_held_environment_object.get()->get_component<Sprite_component>() };

        if (sprite_component)
        {
            sprite_component->get()->render();
            return;
        }
    }
}

std::shared_ptr<Body_part> Tile::get_held_body_part()
{
    return m_held_body_part;
}

std::set<std::shared_ptr<Food>> Tile::get_held_foods() const
{
    return m_held_foods;
}
