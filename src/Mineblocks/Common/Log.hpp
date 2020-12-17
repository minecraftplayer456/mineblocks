#pragma once

#include <spdlog/spdlog.h>

namespace Mineblocks {
    enum class LogCategory { Common, Core };

    auto LogCategoryToString(LogCategory category) -> const char*;

    class Logger {
      public:
        Logger();

        template <typename T, typename... Args>
        void Log(spdlog::level::level_enum level, LogCategory category, const T& msg, Args&&... args){
            std::string format =
                fmt::format("[{}] {}", LogCategoryToString(category), msg);
            logger->template log(level, format, std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        void Trace(LogCategory category, const T& msg, Args&&... args)
        {
            Log(spdlog::level::trace, category, msg, std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        void Debug(LogCategory category, const T& msg, Args&&... args)
        {
            Log(spdlog::level::debug, category, msg, std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        void Info(LogCategory category, const T& msg, Args&&... args)
        {
            Log(spdlog::level::info, category, msg, std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        void Warn(LogCategory category, const T& msg, Args&&... args)
        {
            Log(spdlog::level::warn, category, msg, std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        void Error(LogCategory category, const T& msg, Args&&... args)
        {
            Log(spdlog::level::err, category, msg, std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        void Critical(LogCategory category, const T& msg, Args&&... args)
        {
            Log(spdlog::level::critical, category, msg, std::forward<Args>(args)...);
        }

      private:
        std::shared_ptr<spdlog::logger> logger;
    };

    class Log{
      public:
        static auto GetLogger() -> Logger&;

      private:
        static Logger logger;
    };
} // namespace Mineblocks


#ifdef CONFIGURATION_DEBUG
#define LOG_DEBUG_TRACE(...) ::Mineblocks::Log::GetLogger.Trace(__VA_ARGS__)
#define LOG_DEBUG_DEBUG(...) ::Mineblocks::Log::GetLogger.Debug(__VA_ARGS__)
#define LOG_DEBUG_INFO(...) ::Mineblocks::Log::GetLogger.Info(__VA_ARGS__)
#define LOG_DEBUG_WARN(...) ::Mineblocks::Log::GetLogger.Warn(__VA_ARGS__)
#define LOG_DEBUG_ERROR(...) ::Mineblocks::Log::GetLogger.Error(__VA_ARGS__)
#define LOG_DEBUG_CRITICAL(...) ::Mineblocks::Log::GetLogger.Critical(__VA_ARGS__)
#else
#define LOG_DEBUG_TRACE(...)
#define LOG_DEBUG_DEBUG(...)
#define LOG_DEBUG_INFO(...)
#define LOG_DEBUG_WARN(...)
#define LOG_DEBUG_ERROR(...)
#define LOG_DEBUG_CRITICAL(...)
#endif

#define LOG_TRACE(...) ::Mineblocks::Log::GetLogger.Trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::Mineblocks::Log::GetLogger.Debug(__VA_ARGS__)
#define LOG_INFO(...) ::Mineblocks::Log::GetLogger.Info(__VA_ARGS__)
#define LOG_WARN(...) ::Mineblocks::Log::GetLogger.Warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Mineblocks::Log::GetLogger.Error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Mineblocks::Log::GetLogger.Critical(__VA_ARGS__)
