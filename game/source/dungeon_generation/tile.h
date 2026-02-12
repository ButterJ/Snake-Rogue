#pragma once

#include "body_part.h"
#include "food.h"
#include "game_object.h"

#include <memory>
#include <set>
#include <vector>

class Tile // TODO: Rewrite, as it is pretty hardcoded right now
{
  public:
    enum Occupant_type
    {
        environment_object,
        body_part
    };

  public:
    bool is_occupied() const;
    void add_game_object(Occupant_type tile_occupant_type, std::shared_ptr<Game_object> game_object);
    void remove_game_object(Occupant_type Tile_occupant_type);
    void render() const;

    // TODO: The food things are for testing if set works with my custom data type. Should be rewritten later
    void add_food(std::shared_ptr<Food> food);
    void remove_food(std::shared_ptr<Food> food);
    std::set<std::shared_ptr<Food>> get_held_foods() const;
    void remove_all_foods();

    std::shared_ptr<Body_part> get_held_body_part();

  private:
    std::shared_ptr<Game_object> m_held_environment_object {};
    std::shared_ptr<Body_part> m_held_body_part {};
    std::set<std::shared_ptr<Food>> m_held_foods {};
};
