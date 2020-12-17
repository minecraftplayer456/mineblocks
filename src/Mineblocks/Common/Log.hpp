#pragma once

#include <spdlog/spdlog.h>

namespace Mineblocks {
    enum class LogCategory {
        All,
        Common,
        Core
    };

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
#define LOG_DEBUG_TRACE(Category, ...) Mineblocks::Log::GetLogger().Trace(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_DEBUG_DEBUG(Category, ...) Mineblocks::Log::GetLogger().Debug(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_DEBUG_INFO(Category, ...) Mineblocks::Log::GetLogger().Info(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_DEBUG_WARN(Category, ...) Mineblocks::Log::GetLogger().Warn(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_DEBUG_ERROR(Category, ...) Mineblocks::Log::GetLogger().Error(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_DEBUG_CRITICAL(Category, ...) Mineblocks::Log::GetLogger().Critical(Mineblocks::LogCategory::Category, __VA_ARGS__)
#else
#define LOG_DEBUG_TRACE(Category, ...)
#define LOG_DEBUG_DEBUG(Category, ...)
#define LOG_DEBUG_INFO(Category, ...)
#define LOG_DEBUG_WARN(Category, ...)
#define LOG_DEBUG_ERROR(Category, ...)
#define LOG_DEBUG_CRITICAL(Category, ...)
#endif

#define LOG_TRACE(Category, ...) Mineblocks::Log::GetLogger().Trace(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_DEBUG(Category, ...) Mineblocks::Log::GetLogger().Debug(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_INFO(Category, ...) Mineblocks::Log::GetLogger().Info(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_WARN(Category, ...) Mineblocks::Log::GetLogger().Warn(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_ERROR(Category, ...) Mineblocks::Log::GetLogger().Error(Mineblocks::LogCategory::Category, __VA_ARGS__)
#define LOG_CRITICAL(Category, ...) Mineblocks::Log::GetLogger().Critical(Mineblocks::LogCategory::Category, __VA_ARGS__)
