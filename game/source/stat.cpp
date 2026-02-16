#include "stat.h"

#include "timed_stat_modifier.h"

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

void Stat::apply_modifier(std::shared_ptr<Stat_modifier> modifier)
{
    m_modifiers.insert(modifier);

    auto timed_modifier { std::dynamic_pointer_cast<Timed_stat_modifier>(modifier) };
    if (timed_modifier)
    {
        auto on_modifier_expired_lambda { [this, timed_modifier]()
                                          { remove_modifier(timed_modifier); } };
        timed_modifier->On_expired_callback.append(on_modifier_expired_lambda);
    }

    float new_value { recalculate_value() };
    set_value(new_value);
}

void Stat::remove_modifier(std::shared_ptr<Stat_modifier> modifier)
{
    auto it { m_modifiers.find(modifier) };

    if (it != m_modifiers.end())
    {
        m_modifiers.erase(it);
    }

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
        if (modifier->get_type() == Stat_modifier::Type::percent_multiplicative)
        {
            product_percent_multiplicative *= 1 + modifier->get_value();
        }
        else
        {
            float& sum_to_add_to { modifier->get_type() == Stat_modifier::Type::flat ? sum_flat : sum_percent_additive };
            sum_to_add_to += modifier->get_value();
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
