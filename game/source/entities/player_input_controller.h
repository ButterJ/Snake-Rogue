#pragma once

#include "input_controller.h"

#include <optional>

class Player_input_controller : public Input_controller
{
  public:
    void start_deciding_on_action() override;
    void process_input();

  private:
    bool m_is_listening_to_input { false };
};
