#pragma once

#include "component.h"

#include <concepts>
#include <memory>
#include <optional>
#include <vector>

class Game_object
{
  public:
    virtual ~Game_object() {}

    template <typename T_component>
        requires std::derived_from<T_component, Component>
    std::optional<std::shared_ptr<T_component>> get_component()
    {
        for (auto& component : components)
        {
            auto casted_component = std::dynamic_pointer_cast<T_component>(component);

            if (casted_component)
            {
                return casted_component;
            }
        }

        return std::nullopt;
    }

  protected:
    std::vector<std::shared_ptr<Component>> components {};
};
