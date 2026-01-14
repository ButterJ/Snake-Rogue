#pragma once

#include "component.h"

#include "eventpp/callbacklist.h"

class Health_component : public Component
{
  public:
    Health_component(int max_health) : m_max_health { max_health } // TODO: Should be in .cpp file
    {
        m_health = max_health;
    }

    void set_max_health(int max_health);
    void change_max_health(int max_health);
    void change_health(int health_change);
    void set_health(int health);

    void on_death();

    eventpp::CallbackList<void()> On_death_callback {};

  private:
    int m_max_health { 100 };
    int m_health { 100 };
};
