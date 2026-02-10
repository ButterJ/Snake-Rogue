#pragma once

#include <vector>

struct Direction
{
    int x { 0 };
    int y { 0 };

    static const Direction Up;
    static const Direction Right;
    static const Direction Down;
    static const Direction Left;
    static const Direction Zero;

    static const std::vector<Direction> Orthogonal_directions;

    Direction& operator+=(const Direction& direction);
    bool operator!=(const Direction& direction) const;
    bool operator==(const Direction& direction) const;
    Direction operator*(int multiplicator) const;

    Direction get_opposite_direction();
};
