#pragma once

class Stat_modifier
{
  public:
    enum Type
    {
        flat,
        percent_additive,
        percent_multiplicative
    };

    Stat_modifier(Type type, float value);

    virtual ~Stat_modifier() = default;

    bool operator<(const Stat_modifier& other) const;

    Type get_type() const;
    float get_value() const;

  protected:
    Type m_type { flat };
    float m_value {};
};
