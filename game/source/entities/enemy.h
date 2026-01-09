#pragma once

#include "body_part.h"
#include "position.h"
#include "sprite_component.h"
#include "sprite_renderer.h"
#include "sprite_specification.h"
#include "transform_component.h"
#include "turn_based_entity.h"

#include <memory>

class Enemy : public Turn_based_entity // TODO: Right now this is a class to test out enemies in the game. Should probably be named Monster or Creature and be a base clas
{
  public:
    Enemy(Sprite_renderer& p_sprite_renderer, Sprite_specification p_sprite_specification);

  protected:
    void take_turn() override;

    std::shared_ptr<Body_part> body_part;
    Sprite_renderer& sprite_renderer;
    Sprite_specification sprite_specification;
};
