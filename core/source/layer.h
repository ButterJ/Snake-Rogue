#pragma once

#include <concepts>
#include <memory>

namespace Core
{

    class Layer
    {
      public:
        virtual ~Layer() = default;

        virtual void on_start() {}
        virtual void on_update(float delta_time) {}
        virtual void on_render() {}
        virtual void on_stop() {}

        // TODO: Layer transitioning needs to be implemented once it is of use
        //   template <std::derived_from<Layer> T, typename... Args>
        //   void transition_to(Args&&... args)
        //   {
        //       queue_transition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
        //   }

        // private:
        //   void queue_transition(std::unique_ptr<Layer> layer);
    };

} // namespace Core
