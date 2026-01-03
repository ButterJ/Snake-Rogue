#pragma once

struct Tile
{
  enum class Type
  {
    none,
    wall,
    floor,
  };

  Type type {};
};
