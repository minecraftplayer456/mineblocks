#pragma once

#include "Engine/Util/ClassAttribs.hpp"

namespace Engine {
    template <typename T>
    class Singleton : public NonCopyable {
      public:
        static auto Get() -> std::shared_ptr<T>
        {
            return instance;
        }

      protected:
        inline static std::shared_ptr<T> instance;

        static auto Create() -> bool
        {
            instance = std::make_shared<T>();
            return true;
        }
    };
} // namespace Engine
