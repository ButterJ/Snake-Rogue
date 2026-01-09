#include "position.h"

Position Position::operator+(const Direction& direction) const
{
    return Position { .x { x + direction.x }, .y { y + direction.y } };
}

Position& Position::operator+=(const Direction& direction)
{
    x += direction.x;
    y += direction.y;

    return *this;
}
