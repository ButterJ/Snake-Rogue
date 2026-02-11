#pragma once

#include "eventpp/callbacklist.h"

class Resource_bar
{
  public:
    Resource_bar(int max_value) : m_max_value { max_value } {}

    void change_value(int change);
    void set_value(int value);
    void change_max_value(int change);
    void set_max_value(int max_value);

    eventpp::CallbackList<void()> On_bar_filled_callback {};

  private:
    int m_value { 0 };
    int m_max_value { 100 };

    void send_callback_if_bar_is_full() const;
};
