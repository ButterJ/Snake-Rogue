#pragma once

#include "turn_based_entity.h"

#include "action_result.h"
#include "body_part.h"
#include "direction.h"
#include "position.h"
#include "sprite_specification.h"

#include <concepts>
#include <list>
#include <memory>

template <typename T_turn_based_entity>
    requires(std::derived_from<T_turn_based_entity, Turn_based_entity>)
class Creature : public T_turn_based_entity // TODO: Add max body parts restriction
{
  public:
    Creature(int number_of_body_parts, const Sprite_specification& sprite_specification);
    virtual Action_result set_position(const Position& position) = 0;
    virtual Action_result move(const Direction& direction) = 0;

  protected:
    std::shared_ptr<Body_part> create_body_part();
    void add_body_part(std::shared_ptr<Body_part> body_part);
    virtual void on_body_part_death(std::shared_ptr<Body_part> dead_body_part);

    std::list<std::shared_ptr<Body_part>> body_parts {};
    int m_max_body_parts { 3 };
    Sprite_specification m_sprite_specification;
};

template <typename T_turn_based_entity>
    requires(std::derived_from<T_turn_based_entity, Turn_based_entity>)
Creature<T_turn_based_entity>::Creature(int number_of_body_parts, const Sprite_specification& sprite_specification) : m_max_body_parts { number_of_body_parts }, m_sprite_specification { sprite_specification }
{
    for (int i = 0; i < number_of_body_parts; i++)
    {
        std::shared_ptr<Body_part> body_part { create_body_part() };
        add_body_part(body_part);
    }
}

template <typename T_turn_based_entity>
    requires(std::derived_from<T_turn_based_entity, Turn_based_entity>)
std::shared_ptr<Body_part> Creature<T_turn_based_entity>::create_body_part()
{
    auto transform_component = std::make_shared<Transform_component>();

    auto sprite_component = std::make_shared<Sprite_component>(m_sprite_specification, transform_component);
    auto body_part = std::make_shared<Body_part>(sprite_component, transform_component);

    return body_part;
}

template <typename T_turn_based_entity>
    requires(std::derived_from<T_turn_based_entity, Turn_based_entity>)
void Creature<T_turn_based_entity>::add_body_part(std::shared_ptr<Body_part> body_part)
{
    body_parts.push_back(body_part);
    body_part->On_death_callback.append([this, body_part]()
                                        { on_body_part_death(body_part); });
}

template <typename T_turn_based_entity>
    requires(std::derived_from<T_turn_based_entity, Turn_based_entity>)
void Creature<T_turn_based_entity>::on_body_part_death(std::shared_ptr<Body_part> body_part)
{
}
