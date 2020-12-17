#include "Log.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Mineblocks {
    auto LogCategoryToString(LogCategory category) -> const char*
    {
        switch (category) {
            case LogCategory::Common:
                return "Common";
            case LogCategory::Core:
                return "Core";
        }
        return "Unknown-Category";
    }

    Logger::Logger()
    {
        std::vector<spdlog::sink_ptr> logSinks;

        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
        logSinks.emplace_back(
            std::make_shared<spdlog::sinks::basic_file_sink_st>("Game.log", true));

        logger = std::make_shared<spdlog::logger>("Mineblocks", std::begin(logSinks),
                                                        std::end(logSinks));

        spdlog::register_logger(logger);

        logger->set_level(spdlog::level::trace);
    }

    Logger Log::logger;

    auto Log::GetLogger() -> Logger&
    {
        return logger;
    }
} // namespace Mineblocks