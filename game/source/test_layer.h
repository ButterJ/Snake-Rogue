#pragma once

#include "layer.h"

class Test_layer : public Core::Layer
{
  public:
    void on_start() override;
    void on_update(float delta_time) override {}
    void on_render() override {}
    void on_stop() override {}
};
