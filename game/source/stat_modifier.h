#pragma once

struct Stat_modifier
{
    enum Type
    {
        flat,
        percent_additive,
        percent_multiplicative
    };

    bool operator<(const Stat_modifier& other) const;

    float value {};
    Type type { flat };
};
