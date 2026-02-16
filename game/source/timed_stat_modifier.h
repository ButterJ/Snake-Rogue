#pragma once

#include "stat_modifier.h"

#include "turn_based_entity.h"

#include "eventpp/callbacklist.h"

#include <memory>

class Timed_stat_modifier : public Stat_modifier
{
  public:
    Timed_stat_modifier(Stat_modifier::Type type, float value, int duration, std::shared_ptr<Turn_based_entity> modified_entity);

    eventpp::CallbackList<void()> On_expired_callback {};

  private:
    void on_turn_finished();

    int m_remaining_turns {};
    std::shared_ptr<Turn_based_entity> m_modified_entity {};
    eventpp::internal_::CallbackListBase<void(), eventpp::DefaultPolicies>::Handle on_turn_finished_handle {};
};
