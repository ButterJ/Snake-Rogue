#pragma once

#include "layer.h"

#include "colour.h"

class Background_layer : public Core::Layer
{
  public:
    void on_render() override;

  private:
    const Colour m_background_colour { 20, 10, 30, 255 };
};
