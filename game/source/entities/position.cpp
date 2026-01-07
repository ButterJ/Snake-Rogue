#include "position.h"

Position Position::operator+(const Direction& direction) const
{
    return Position {.x {x + direction.x}, .y {y + direction.y}};
}
