#pragma once

#include "colour.h"
#include "component.h"
#include "game.h"
#include "position.h"
#include "sdl_manager.h"
#include "sprite_specification.h"
#include "transform_component.h"

#include <memory>
#include <string>

class Sprite_component : public Component
{
  public:
    Sprite_component(Sprite_specification sprite_specification, std::shared_ptr<Transform_component> transform_component)
        : m_sprite_specification { sprite_specification }, m_transform_component { transform_component }
    {
    }

    void render();

    void set_colour(Colour colour);

  private:
    Sprite_specification m_sprite_specification;
    std::shared_ptr<Transform_component> m_transform_component;
    Colour m_colour {};

    Core::Sdl_manager& sdl_manager { Core::Game::get_instance().get_sdl_manager() };
};
