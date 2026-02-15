#pragma once

#include "input_action.h"

#include "eventpp/callbacklist.h"

#include <memory>

// TODO: Decide if a better name is better
// TODO: This should probably be an abstract class
class Input_controller
{
  public:
    virtual void start_deciding_on_action() = 0;
    eventpp::CallbackList<void(std::shared_ptr<Input_action>)> On_action_decided {};

    virtual ~Input_controller() = 0;
};
