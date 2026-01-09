#pragma once

namespace Core
{

    template <typename T>
    class Singleton
    {
      public:
        static T& get_instance()
        {
            static T instance;
            return instance;
        }

        Singleton(const Singleton&) = delete;
        void operator=(const Singleton&) = delete;

      protected:
        Singleton() {}
        ~Singleton() {}
    };

} // namespace Core
