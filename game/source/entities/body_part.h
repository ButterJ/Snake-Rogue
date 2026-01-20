#pragma once

#include "action_result.h"
#include "collider_component.h"
#include "direction.h"
#include "game_object.h"
#include "health_component.h"
#include "position.h"
#include "sprite_component.h"
#include "transform_component.h"

#include "eventpp/callbacklist.h"
#include <SDL3/SDL_log.h>

#include <memory>

class Body_part : public Game_object
{
  public:
    Body_part(std::shared_ptr<Sprite_component> sprite_component, std::shared_ptr<Transform_component> transform_component) // TODO: Move constructor into cpp file
        : m_sprite_component { sprite_component }, m_transform_component { transform_component }, m_collider_component { std::make_shared<Collider_component>() }, m_health_component { std::make_shared<Health_component>(100) }
    {
        components.push_back(m_sprite_component);
        components.push_back(m_transform_component);
        components.push_back(m_collider_component);
        components.push_back(m_health_component);
        m_health_component.get()->On_death_callback.append([this]()
                                                           { on_death(); });
    }

    Action_result set_position(const Position& position);
    Action_result move(const Direction& direction);
    const Position& get_position() const;
    void change_health(int health_change);

    std::shared_ptr<Transform_component> get_transform_component();

    eventpp::CallbackList<void()> On_death_callback {};

    ~Body_part() { SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Body part destroyed"); }

  private:
    void on_death();

    std::shared_ptr<Sprite_component> m_sprite_component;
    std::shared_ptr<Transform_component> m_transform_component;
    std::shared_ptr<Collider_component> m_collider_component;
    std::shared_ptr<Health_component> m_health_component;
};
