#pragma once

#include "body_part.h"
#include "direction.h"
#include "turn_based_entity.h"

#include <concepts>
#include <list>
#include <memory>

template <typename T_turn_based_entity>
    requires(std::derived_from<T_turn_based_entity, Turn_based_entity>)
class Creature : public T_turn_based_entity // TODO: Add max body parts restriction
{
  public:
    virtual void move(const Direction& direction) = 0;
    virtual void add_body_part(std::shared_ptr<Body_part> body_part) = 0;
    virtual void render() = 0;

  protected:
    std::list<std::shared_ptr<Body_part>> body_parts {};
};
