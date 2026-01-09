#pragma once

#include "game.h"
#include "sdl_manager.h"
#include "sprite_component.h"
#include "sprite_specification.h"

#include <map>
#include <memory>

class Sprite_renderer
{
  public:
    void register_sprite_component(std::shared_ptr<Sprite_component> sprite_component);
    void release_sprite_component(std::shared_ptr<Sprite_component> sprite_component);

    void render_sprites() const;

  private:
    void render_sprite(std::shared_ptr<Sprite_component> sprite_component) const;
    std::map<Id, std::shared_ptr<Sprite_component>> sprite_components {};

    Core::Sdl_manager& sdl_manager { Core::Game::get_instance().get_sdl_manager() };
};
