#include "direction.h"

const Direction Direction::Up { 0, -1 };
const Direction Direction::Right { 1, 0 };
const Direction Direction::Down { 0, 1 };
const Direction Direction::Left { -1, 0 };
const Direction Direction::Zero { 0, 0 };

const std::vector<Direction> Direction::Orthogonal_directions { Direction::Up, Direction::Right, Direction::Down, Direction::Left };

Direction& Direction::operator+=(const Direction& direction)
{
    x += direction.x;
    y += direction.y;

    return *this;
}

bool Direction::operator!=(const Direction& direction) const
{
    return x != direction.x || y != direction.y ? true : false;
}

bool Direction::operator==(const Direction& direction) const
{
    return x == direction.x && y == direction.y ? true : false;
}

Direction Direction::operator*(int multiplicator) const
{
    return { x * multiplicator, y * multiplicator };
}

Direction Direction::get_opposite_direction()
{
    return Direction { x * -1, y * -1 };
}
