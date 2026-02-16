#include "timed_stat_modifier.h"

Timed_stat_modifier::Timed_stat_modifier(Stat_modifier::Type type, float value, int duration, std::shared_ptr<Turn_based_entity> modified_entity)
    : Stat_modifier(type, value)
    , m_remaining_turns { duration }
    , m_modified_entity { modified_entity }
{
    auto on_turn_finished_lambda {
        [this]()
        { on_turn_finished(); }
    };
    on_turn_finished_handle = m_modified_entity->On_turn_finished_callback.append(on_turn_finished_lambda);
}

void Timed_stat_modifier::on_turn_finished()
{
    m_remaining_turns--;

    if (m_remaining_turns <= 0)
    {
        On_expired_callback();
        On_expired_callback.empty();
        m_modified_entity->On_turn_finished_callback.remove(on_turn_finished_handle);
    }
}
