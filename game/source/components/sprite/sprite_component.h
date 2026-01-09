#pragma once

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
    Sprite_component(Sprite_specification p_sprite_specification, std::shared_ptr<Transform_component> p_transform_component);

    void render();

  private:
    Sprite_specification sprite_specification;
    std::shared_ptr<Transform_component> transform_component;

    Core::Sdl_manager& sdl_manager { Core::Game::get_instance().get_sdl_manager() };
};
