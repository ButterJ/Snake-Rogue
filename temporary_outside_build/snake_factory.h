#pragma once

#include "body_part.h"
#include "snake.h"
#include "spritesheet.h"

class Snake_factory
{
  public:
    void create_creature(int number_of_body_parts);

    std::shared_ptr<Snake> get_creature() const;

  private:
    std::shared_ptr<Body_part> create_body_part();

    Spritesheet brogue_tiles { "data/tiles.png", 128.0f, 232.0f }; // TODO: Temporary
    std::shared_ptr<Snake> creature { std::make_shared<Snake>() };
};
