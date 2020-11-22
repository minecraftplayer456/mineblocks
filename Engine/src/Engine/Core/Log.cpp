#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine {
    std::shared_ptr<spdlog::logger> Log::clientLogger;
    std::shared_ptr<spdlog::logger> Log::coreLogger;

    bool Log::Init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("Game.log", true));

        coreLogger =
            std::make_shared<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));

        spdlog::register_logger(coreLogger);

        coreLogger->set_level(spdlog::level::trace);
        coreLogger->flush_on(spdlog::level::trace);

        clientLogger =
            std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));

        spdlog::register_logger(clientLogger);

        clientLogger->set_level(spdlog::level::trace);
        clientLogger->flush_on(spdlog::level::trace);

        return true;
    }
} // namespace Engine