#pragma once

#include "game_object.h"

#include <memory>
#include <unordered_map>
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

  private:
    std::shared_ptr<Game_object> held_environment_object {};
    std::shared_ptr<Game_object> held_body_part {};
};
