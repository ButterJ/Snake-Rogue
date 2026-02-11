#include "resource_bar.h"

#include <algorithm>

void Resource_bar::change_value(int change)
{
    m_value = std::clamp(m_value + change, 0, m_max_value);
    send_callback_if_bar_is_full();
}

void Resource_bar::set_value(int value)
{
    m_value = std::clamp(value, 0, m_max_value);

    send_callback_if_bar_is_full();
}

void Resource_bar::change_max_value(int change)
{
    m_max_value = std::max(m_max_value + change, 1);
    m_value = std::min(m_value, m_max_value);
    send_callback_if_bar_is_full();
}

void Resource_bar::set_max_value(int max_value)
{
    assert(max_value > 0 && "The max value for the resource bar needs to be bigger than 0");

    m_max_value = max_value;
    m_value = std::min(m_value, m_max_value);
    send_callback_if_bar_is_full();
}

void Resource_bar::send_callback_if_bar_is_full() const
{
    if (m_value == m_max_value)
    {
        On_bar_filled_callback();
    }
}
