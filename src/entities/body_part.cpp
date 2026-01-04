#include "body_part.h"

const Position& Body_part::get_position() const
{
    return position;
}

void Body_part::set_position(const Position& position)
{
    this->position = position;
}
