#pragma once

using Id = int;

class Component
{
  public:
    Component() : id { next_id++ } {}
    virtual ~Component() = default;

    int get_id() const;

  protected:
    static Id next_id; // Set in component.cpp
    Id id {};          // TODO: This id could potentially overflow, also see if it is even needed
};
