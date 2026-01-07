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

    template <std::derived_from<Layer> T, typename... Args>
    void TransitionTo(Args&&... args)
    {
        QueueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
    }

  private:
    void QueueTransition(std::unique_ptr<Layer> layer);
};

} // namespace Core
