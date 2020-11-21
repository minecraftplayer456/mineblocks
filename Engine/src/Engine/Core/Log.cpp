#include "Log.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine {
    std::shared_ptr<spdlog::logger> Log::ClientLogger;
    std::shared_ptr<spdlog::logger> Log::CoreLogger;

    bool Log::Init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("Game.log", true));

        CoreLogger =
            std::make_shared<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));
        spdlog::register_logger(CoreLogger);
        CoreLogger->set_level(spdlog::level::trace);
        CoreLogger->flush_on(spdlog::level::trace);

        ClientLogger =
            std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(ClientLogger);
        ClientLogger->set_level(spdlog::level::trace);
        ClientLogger->flush_on(spdlog::level::trace);

        return true;
    }
} // namespace Engine