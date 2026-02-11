#pragma once

#include "component.h"

#include <concepts>
#include <memory>
#include <optional>
#include <vector>

// TODO: I commented out the id functionality as I don't think it is needed right now. Remove this once Im sure it is not needed
class Game_object : public std::enable_shared_from_this<Game_object>
{
  public:
    // Game_object()
    // {
    //     m_id = s_next_id++;
    // }
    virtual ~Game_object() {}

    // bool operator==(const Game_object& other) const
    // {
    //     return m_id == other.m_id;
    // }

    // bool operator<(const Game_object& other) const
    // {
    //     return m_id < other.m_id;
    // }

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

    //   private:
    //     static inline int s_next_id { 0 };
    //     int m_id;
};
