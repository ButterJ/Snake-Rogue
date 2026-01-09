#include "body_part.h"

std::shared_ptr<Transform_component> Body_part::get_transform_component()
{
    return transform_component;
}

void Body_part::move(const Direction& direction)
{
    transform_component.get()->position += direction;
}

void Body_part::render()
{
    sprite_component.get()->render();
}
