#include "direction.h"

const Direction Direction::Up { 0, -1 };
const Direction Direction::Right { 1, 0 };
const Direction Direction::Down { 0, 1 };
const Direction Direction::Left { -1, 0 };
const Direction Direction::Zero { 0, 0 };

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
