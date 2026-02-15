#include "stat.h"

#include <algorithm>

Stat::Stat(float value, std::optional<float> minimum_value, std::optional<float> maximum_value)
    : m_value { value }
    , m_minimum_value { minimum_value }
    , m_maximum_value { maximum_value }
{
}

float Stat::get_value() const
{
    if (m_minimum_value.has_value())
    {
        if (m_value <= m_minimum_value.value())
        {
            return m_minimum_value.value();
        }
    }

    if (m_maximum_value.has_value())
    {
        if (m_value >= m_maximum_value.value())
        {
            return m_maximum_value.value();
        }
    }

    return m_value;
}
