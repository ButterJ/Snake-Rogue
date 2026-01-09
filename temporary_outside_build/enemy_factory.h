#pragma once

#include "body_part.h"
#include "enemy.h"
#include "spritesheet.h"

class Enemy_factory
{
  public:
    void create_creature(int number_of_body_parts);

    std::shared_ptr<Enemy> get_creature() const;

  private:
    std::shared_ptr<Body_part> create_body_part();

    Spritesheet brogue_tiles { "data/tiles.png", 128.0f, 232.0f }; // TODO: Temporary
    std::shared_ptr<Enemy> creature { std::make_shared<Enemy>() };
};
