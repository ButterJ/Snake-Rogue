#pragma once

#include "body_part.h"
#include "spritesheet.h"

#include <memory>

template <typename T_creature>
class Creature_builder // TODO: Rename to
{
  public:
    void create_creature(int number_of_body_parts);

    std::shared_ptr<T_creature> get_creature() const;

  private:
    std::shared_ptr<Body_part> create_body_part();

    Spritesheet brogue_tiles { "data/tiles.png", 128.0f, 232.0f }; // TODO: Temporary
    std::shared_ptr<T_creature> creature { std::make_shared<T_creature>() };
};

#include "creature_builder.cpp"
