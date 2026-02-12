#pragma once

#include "layer.h"
#include "sdl_manager.h"
#include "singleton.h"

#include <memory>
#include <vector>

namespace Core
{

    class Game : public Singleton<Game>
    {
      public:
        void start();
        void update();
        void stop();

        template <typename TLayer>
            requires(std::is_base_of_v<Layer, TLayer>)
        void push_layer()
        {
            m_layer_stack.push_back(std::make_unique<TLayer>());
        }

        template <typename TLayer>
            requires(std::is_base_of_v<Layer, TLayer>)
        TLayer* get_layer()
        {
            for (const auto& layer : m_layer_stack)
            {
                if (auto casted = dynamic_cast<TLayer*>(layer.get()))
                    return casted;
            }
            return nullptr;
        }

        Sdl_manager& get_sdl_manager();

      private:
        Sdl_manager m_sdl_manager {};

        std::vector<std::unique_ptr<Layer>> m_layer_stack {};

        uint64_t m_previous_time {};
    };

} // namespace Core
