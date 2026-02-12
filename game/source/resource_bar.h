#pragma once

#include "eventpp/callbacklist.h"

class Resource_bar
{
  public:
    Resource_bar(int max_value);

    void set_max_value(int max_value);
    void change_max_value(int change);

    void change_value(int change);
    void set_value(int value);

    eventpp::CallbackList<void()> On_bar_filled_callback {};

  private:
    void send_callback_if_bar_is_full() const;

    int m_max_value { 100 };
    int m_value { 0 };
};
