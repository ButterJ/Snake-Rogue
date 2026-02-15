#include "stat.h"

#include <algorithm>

Stat::Stat(float value, std::optional<float> minimum_value, std::optional<float> maximum_value)
    : m_initial_value { value }
    , m_value { value }
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

void Stat::apply_modifier(Stat_modifier modifier)
{
    m_modifiers.push_back(modifier);

    float new_value { recalculate_value() };
    set_value(new_value);
}

// Calculates the value of the stat by applying all of its modifiers in the correct order.
float Stat::recalculate_value()
{
    float sum_flat { 0 };
    float sum_percent_additive { 1 };
    float product_percent_multiplicative { 1 };

    for (const auto& modifier : m_modifiers)
    {
        if (modifier.type == Stat_modifier::Type::percent_multiplicative)
        {
            product_percent_multiplicative *= 1 + modifier.value;
        }
        else
        {
            float& sum_to_add_to { modifier.type == Stat_modifier::Type::flat ? sum_flat : sum_percent_additive };
            sum_to_add_to += modifier.value;
        }
    }

    float recalculated_value { m_initial_value };
    recalculated_value += sum_flat;
    recalculated_value *= sum_percent_additive;
    recalculated_value *= product_percent_multiplicative;

    return recalculated_value;
}

void Stat::set_value(float value)
{
    m_value = value;

    On_value_changed();
}
