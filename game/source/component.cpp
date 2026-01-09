#include "component.h"

int Component::next_id = 0;

int Component::get_id() const
{
    return id;
}
