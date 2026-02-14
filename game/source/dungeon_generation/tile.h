#pragma once

#include "body_part.h"
#include "food.h"
#include "game_object.h"

#include <map>
#include <memory>
#include <set>

class Tile
{
  public:
    enum Occupant_type
    {
        environment_object,
        body_part,
        food
    };

    void add_game_object(Occupant_type tile_occupant_type, std::shared_ptr<Game_object> game_object);
    void remove_game_object(Occupant_type Tile_occupant_type);

    void render() const;

    bool is_occupied() const;

    std::shared_ptr<Body_part> get_held_body_part() const;
    std::set<std::shared_ptr<Food>> get_held_foods() const;

  private:
    bool is_occupied_by_type(Occupant_type occupant_type) const;
    bool render_occupant_type(Occupant_type occupant_type) const;

    std::map<Occupant_type, std::set<std::shared_ptr<Game_object>>> m_held_game_objects {};
};
