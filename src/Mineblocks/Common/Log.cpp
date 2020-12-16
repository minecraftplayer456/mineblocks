#include "Log.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Mineblocks{
    void Log::Initialize()
    {
        std::vector<spdlog::sink_ptr> logSinks;

        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("Game.log", true));

        commonLogger = std::make_shared<spdlog::logger>("Common", std::begin(logSinks), std::end(logSinks));
        coreLogger = std::make_shared<spdlog::logger>("Core", std::begin(logSinks), std::end(logSinks));

        spdlog::register_logger(commonLogger);
        spdlog::register_logger(coreLogger);

        commonLogger->set_level(spdlog::level::trace);
        coreLogger->set_level(spdlog::level::trace);
    }

    auto Log::Common() -> std::shared_ptr<spdlog::logger>
    {
        return commonLogger;
    }
    auto Log::Core() -> std::shared_ptr<spdlog::logger>
    {
        return coreLogger;
    }

    auto Log::LogCategoryToString(LogCategory category) -> const char* {
        switch (category) {
            case LogCategory::Common:
                return "Common";
            case LogCategory::Core:
                return "Core";
        }
        return "Unknown-Category";
    }
}