#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine {
    bool Log::Initialized;

    std::shared_ptr<spdlog::logger> Log::coreLogger;
    std::shared_ptr<spdlog::logger> Log::appLogger;

    auto Log::Init() -> bool
    {
        if (Initialized) {
            return true;
        }

        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("Game.log", true));

        coreLogger = std::make_shared<spdlog::logger>("ENGINE", std::begin(logSinks),
                                                      std::end(logSinks));
        appLogger = std::make_shared<spdlog::logger>("APP", std::begin(logSinks),
                                                     std::end(logSinks));

        spdlog::register_logger(coreLogger);
        spdlog::register_logger(appLogger);

        coreLogger->set_level(spdlog::level::trace);
        appLogger->set_level(spdlog::level::trace);

        coreLogger->flush_on(spdlog::level::trace);
        appLogger->flush_on(spdlog::level::trace);

        return true;
    }
}; // namespace Engine