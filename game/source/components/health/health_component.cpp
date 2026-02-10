#include "health_component.h"

void Health_component::set_max_health(int max_health)
{
    assert(max_health > 0 && "Max health must be greater than zero");

    m_max_health = max_health;

    if (m_health > m_max_health)
    {
        m_health = m_max_health;
    }
}

void Health_component::change_max_health(int max_health)
{
    m_max_health += max_health;

    if (m_max_health < 1)
    {
        m_max_health = 1;
    }

    if (m_health > m_max_health)
    {
        m_health = m_max_health;
    }
}

void Health_component::set_health(int health)
{
    m_health = health;

    if (m_health > m_max_health)
    {
        m_health = m_max_health;
    }
    else if (m_health <= 0)
    {
        m_health = 0;
        on_death();
    }
}

void Health_component::change_health(int health_change)
{
    m_health += health_change;

    if (m_health > m_max_health)
    {
        m_health = m_max_health;
    }
    else if (m_health <= 0)
    {
        m_health = 0;
        on_death();
    }
}

int Health_component::get_health() const
{
    return m_health;
}

int Health_component::get_max_health() const
{
    return m_max_health;
}

void Health_component::on_death()
{
    On_death_callback();
}
