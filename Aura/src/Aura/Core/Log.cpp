#include "Log.h"

#include <filesystem>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "spdlog/async.h"

#include "EASTL/span.h"

namespace
{
    std::shared_ptr<spdlog::logger> s_pLogger;
    static constexpr std::string_view s_pattern = "[%m-%d-%Y %I:%M:%S:%e] [%^%l%$] %v";
}

namespace Aura
{
namespace Log
{
void Init()
{
    std::string const logsDirectory = "logs";
    if (!std::filesystem::exists(logsDirectory))
    {
        std::filesystem::create_directories(logsDirectory);
    }

    spdlog::init_thread_pool(8192, 1);
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(spdlog::level::debug);
    consoleSink->set_pattern(s_pattern.data());

    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/Aura.log", true);
    fileSink->set_level(spdlog::level::trace);
    fileSink->set_pattern(s_pattern.data());

    eastl::array<spdlog::sink_ptr, 2> sinks = {consoleSink, fileSink};
    s_pLogger = std::make_shared<spdlog::async_logger>("aura_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(),
                                                       spdlog::async_overflow_policy::block);
    s_pLogger->set_level(spdlog::level::trace);

    spdlog::register_logger(s_pLogger);
    spdlog::flush_every(std::chrono::seconds(3));

    AURA_LOG("Logger", "Logger initialized");
}

void Shutdown()
{
    AURA_LOG("Logger", "Logger Shutdown");
}

std::shared_ptr<spdlog::logger> GetLogger()
{
    return s_pLogger;
}
} // namespace Log
} // namespace Aura