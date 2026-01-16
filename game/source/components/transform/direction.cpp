#include "direction.h"

Direction& Direction::operator+=(const Direction& direction)
{
    x += direction.x;
    y += direction.y;

    return *this;
}

bool Direction::operator!=(const Direction& direction)
{
    return x != direction.x || y != direction.y ? true : false;
}
