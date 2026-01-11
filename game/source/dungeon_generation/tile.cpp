#include "tile.h"
#include "collider_component.h"
#include "environment_object.h"
#include "i_renderable.h"

bool Tile::is_occupied() const
{
    for (auto game_object : held_game_objects)
    {
        if (game_object.get()->get_component<Collider_component>())
        {
            return true;
        }
    }

    return false;
}

void Tile::add_game_object(std::shared_ptr<Game_object> game_object)
{
    held_game_objects.push_back(game_object);
}

void Tile::render() const
{
    for (auto game_object = held_game_objects.rbegin(); game_object != held_game_objects.rend(); ++game_object)
    {
        auto renderable = std::dynamic_pointer_cast<I_renderable>(*game_object);

        if (!renderable)
        {
            continue;
        }

        renderable.get()->render();
        return;
    }
}
