#include "stat_modifier.h"

Stat_modifier::Stat_modifier(Type type, float value)
    : m_type { type }
    , m_value { value }
{
}

Stat_modifier::Type Stat_modifier::get_type() const
{
    return m_type;
}

float Stat_modifier::get_value() const
{
    return m_value;
}
