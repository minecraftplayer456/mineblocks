#pragma once

#include <spdlog/spdlog.h>

namespace Mineblocks{
    const char LogMsgPrefix[] = "[{}] ";

    enum class LogCategory{
        Common,
        Core
    };

    class Log{
      public:
        static void Initialize();

        static auto Common() -> std::shared_ptr<spdlog::logger>;
        static auto Core() -> std::shared_ptr<spdlog::logger>;

        static auto LogCategoryToString(LogCategory category) -> const char*;

      private:
        static std::shared_ptr<spdlog::logger> commonLogger;
        static std::shared_ptr<spdlog::logger> coreLogger;
    };
}
