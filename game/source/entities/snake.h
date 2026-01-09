#pragma once

#include "body_part.h"
#include "direction.h"
#include "i_player_entity.h"
#include "player_controlled_entity.h"
#include "sprite_component.h"
#include "sprite_renderer.h"
#include "sprite_specification.h"
#include "turn_based_entity.h"

#include <list>
#include <memory>

class Snake : public Player_controlled_entity
{
  public:
    Snake(int number_of_body_parts, Sprite_renderer& p_sprite_renderer, Sprite_specification p_sprite_specification); // TODO: I don't like giving the snake access to the sprite renderer and specification

    const Input_result process_input() override;
    const std::list<std::shared_ptr<Body_part>>& get_body_parts() const;
    void move(const Direction& direction);

  protected:
    void take_turn() override;

  private:
    void add_body_part();

    Sprite_renderer& sprite_renderer;
    Sprite_specification sprite_specification;
    std::list<std::shared_ptr<Body_part>> body_parts {};
};
