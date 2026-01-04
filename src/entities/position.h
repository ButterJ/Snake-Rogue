#pragma once

#include "direction.h"
struct Position
{
    int x {0};
    int y {0};

    Position operator+(const Direction& direction) const;
};
