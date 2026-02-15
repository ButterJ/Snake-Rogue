#pragma once

#include "stat_modifier.h"

#include "eventpp/callbacklist.h"

#include <optional>
#include <set>

// TODO: Consider making this a template class with int or float stats
class Stat
{
  public:
    Stat(float value, std::optional<float> minimum_value = std::nullopt, std::optional<float> maximum_value = std::nullopt);

    float get_value() const;

    void add_modifier(Stat_modifier stat_modifier);
    void remove_modifier(Stat_modifier stat_modifier);

    eventpp::CallbackList<void()> On_value_changed {};

  private:
    void recalculate_value();

    void set_value(float value);

    float m_initial_value {};
    float m_value {};
    std::optional<float> m_minimum_value {};
    std::optional<float> m_maximum_value {};

    std::set<Stat_modifier> m_stat_modifiers {};
};
