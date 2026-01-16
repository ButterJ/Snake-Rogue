#pragma once

struct Direction
{
    int x { 0 };
    int y { 0 };

    Direction& operator+=(const Direction& direction);
    bool operator!=(const Direction& direction);
};
