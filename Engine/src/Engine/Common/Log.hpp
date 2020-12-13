#include <spdlog/spdlog.h>

namespace Engine {
    class Log {
      public:
        static auto Init() -> bool;

        static auto GetCoreLogger() -> std::shared_ptr<spdlog::logger>&
        {
            return coreLogger;
        }

        static auto GetAppLogger() -> std::shared_ptr<spdlog::logger>&
        {
            return appLogger;
        }

      private:
        static bool Initialized;

        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> appLogger;
    };
}; // namespace Engine

#ifdef ENGINE_CONFIGURATION_DEBUG
#define ENGINE_CORE_DEV_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_DEV_DEBUG(...) ::Engine::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define ENGINE_CORE_DEV_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_DEV_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_DEV_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_DEV_CRITICAL(...)                                                    \
    ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ENGINE_DEV_TRACE(...) ::Engine::Log::GetAppLogger()->trace(__VA_ARGS__)
#define ENGINE_DEV_DEBUG(...) ::Engine::Log::GetAppLogger()->debug(__VA_ARGS__)
#define ENGINE_DEV_INFO(...) ::Engine::Log::GetAppLogger()->info(__VA_ARGS__)
#define ENGINE_DEV_WARN(...) ::Engine::Log::GetAppLogger()->warn(__VA_ARGS__)
#define ENGINE_DEV_ERROR(...) ::Engine::Log::GetAppLogger()->error(__VA_ARGS__)
#define ENGINE_DEV_CRITICAL(...) ::Engine::Log::GetAppLogger()->critical(__VA_ARGS__)
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

#define ENGINE_TRACE(...) ::Engine::Log::GetAppLogger()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...) ::Engine::Log::GetAppLogger()->debug(__VA_ARGS__)
#define ENGINE_INFO(...) ::Engine::Log::GetAppLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) ::Engine::Log::GetAppLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Log::GetAppLogger()->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...) ::Engine::Log::GetAppLogger()->critical(__VA_ARGS__)