#include "environment_object.h"

Environment_object::Environment_object(const Position& position)
    : m_transform_component { std::make_shared<Transform_component>(position) }
{
    components.emplace_back(m_transform_component);
}

Environment_object::~Environment_object()
{
}
