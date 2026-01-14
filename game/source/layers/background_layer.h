#pragma once

#include "colour.h"
#include "layer.h"

class Background_layer : public Core::Layer
{
  public:
    void on_render() override;

  private:
    const Colour background_colour { 200, 200, 200, 255 };
};
