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

    Sdl_manager& get_sdl_manager();

    // TODO: Understand push layer and see if I can reorganize it into header and source
    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void push_layer()
    {
        layer_stack.push_back(std::make_unique<TLayer>());
    }

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    TLayer* get_layer()
    {
        for (const auto& layer : layer_stack)
        {
            if (auto casted = dynamic_cast<TLayer*>(layer.get()))
                return casted;
        }
        return nullptr;
    }

  private:
    uint64_t previous_time {};
    std::vector<std::unique_ptr<Layer>> layer_stack {};
    Sdl_manager sdl_manager {};
};

} // namespace Core
