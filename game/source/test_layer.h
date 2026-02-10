#pragma once

#include "layer.h"

#include "game.h"
#include "random_number_generator.h"
#include "sdl_manager.h"

#include <SDL3_image/SDL_image.h>
#include <iostream>

class Test_layer : public Core::Layer
{
  public:
    void on_start() override;
    void on_update(float delta_time) override {}
    void on_render() override {}
    void on_stop() override {}
};
