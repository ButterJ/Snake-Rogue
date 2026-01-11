#pragma once

#include "game_object.h"

#include <memory>
#include <vector>

class Tile // TODO: Add functionality to functions
{
  public:
    bool is_occupied() const;
    void add_game_object(std::shared_ptr<Game_object> game_object);
    void remove_game_object(std::shared_ptr<Game_object> game_object) {}
    void render() const; // Renders the topmost renderable object on the tile

  private:
    std::vector<std::shared_ptr<Game_object>> held_game_objects {};
};
