#pragma once

#include <spdlog/spdlog.h>

namespace Engine {
    class Log {
      public:
        static bool Init();

        inline static const bool Initialized = Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            return CoreLogger;
        }
        static std::shared_ptr<spdlog::logger>& GetClientLogger()
        {
            return ClientLogger;
        }

      private:
        static std::shared_ptr<spdlog::logger> CoreLogger;
        static std::shared_ptr<spdlog::logger> ClientLogger;
    };
} // namespace Engine

#ifdef ENGINE_MODE_DEBUG
#define ENGINE_CORE_DEV_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_DEV_DEBUG(...) ::Engine::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define ENGINE_CORE_DEV_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_DEV_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_DEV_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_DEV_CRITICAL(...)                                                    \
    ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ENGINE_DEV_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_DEV_DEBUG(...) ::Engine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define ENGINE_DEV_INFO(...) ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_DEV_WARN(...) ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_DEV_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGINE_DEV_CRITICAL(...) ::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
#define ENGINE_CORE_DEV_TRACE(...)
#define ENGINE_CORE_DEV_DEBUG(...)
#define ENGINE_CORE_DEV_INFO(...)
#define ENGINE_CORE_DEV_WARN(...)
#define ENGINE_CORE_DEV_ERROR(...)
#define ENGINE_CORE_DEV_CRITICAL(...)

#define ENGINE_DEV_TRACE(...)
#define ENGINE_DEV_DEBUG(...)
#define ENGINE_DEV_INFO(...)
#define ENGINE_DEV_WARN(...)
#define ENGINE_DEV_ERROR(...)
#define ENGINE_DEV_CRITICAL(...)
#endif

#define ENGINE_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_DEBUG(...) ::Engine::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define ENGINE_CORE_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...) ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ENGINE_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...) ::Engine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define ENGINE_INFO(...) ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...) ::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)