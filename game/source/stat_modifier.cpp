#include "stat_modifier.h"

bool Stat_modifier::operator<(const Stat_modifier& other) const
{
    return type < other.type;
}
