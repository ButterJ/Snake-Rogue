#pragma once

struct Direction
{
    int x { 0 };
    int y { 0 };

    static const Direction Up;
    static const Direction Right;
    static const Direction Down;
    static const Direction Left;
    static const Direction Zero;

    // static constexpr Direction Up() { return { 0, 1 }; }
    // static constexpr Direction Down() { return { 0, -1 }; }
    // static constexpr Direction Left() { return { -1, 0 }; }
    // static constexpr Direction Right() { return { 1, 0 }; }
    // static constexpr Direction Zero() { return { 0, 0 }; }

    Direction& operator+=(const Direction& direction);
    bool operator!=(const Direction& direction);
};
