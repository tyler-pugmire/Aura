#pragma once

//#define SPDLOG_USE_STD_FORMAT
#include "spdlog/spdlog.h"
#include "EASTL/string_view.h"

namespace Aura
{
    namespace Log
    {
        enum class Level
        {
            Trace,
            Log,
            Debug,
            Warning,
            Error,
            Critical
        };

        void Init();
        void Shutdown();

        std::shared_ptr<spdlog::logger> GetLogger();

        template<typename... Args>
        void PrintMessage(Level level, std::string_view tag, fmt::format_string<Args...> log, Args &&...args);
    }

    #define AURA_TRACE(tag, str, ...) Aura::Log::PrintMessage(Aura::Log::Level::Trace, tag, str, __VA_ARGS__);
    #define AURA_LOG(tag, str, ...) Aura::Log::PrintMessage(Aura::Log::Level::Log, tag, str, __VA_ARGS__);
    #define AURA_DEBUG(tag, str, ...) Aura::Log::PrintMessage(Aura::Log::Level::Debug, tag, str, __VA_ARGS__);
    #define AURA_WARN(tag, str, ...) Aura::Log::PrintMessage(Aura::Log::Level::Warning, tag, str, __VA_ARGS__);
    #define AURA_ERROR(tag, str, ...) Aura::Log::PrintMessage(Aura::Log::Level::Error, tag, str, __VA_ARGS__);
    #define AURA_CRITICAL(tag, str, ...) Aura::Log::PrintMessage(Aura::Log::Level::Critical, tag, str, __VA_ARGS__);

    template<typename... Args>
    void Aura::Log::PrintMessage(Level level, std::string_view tag, fmt::format_string<Args...> log, Args &&...args)
    {
        constexpr std::string_view msg("[{0}] {1}");
        const std::string logMessage = fmt::vformat(log, fmt::make_format_args(args...));
        switch (level)
        {
        case Aura::Log::Level::Trace:
            Aura::Log::GetLogger()->trace(msg, tag, logMessage);
            break;
        case Aura::Log::Level::Log:
            Aura::Log::GetLogger()->info(msg, tag, logMessage);
            break;
        case Aura::Log::Level::Debug:
            Aura::Log::GetLogger()->debug(msg, tag, logMessage);
            break;
        case Aura::Log::Level::Warning:
            Aura::Log::GetLogger()->warn(msg, tag, logMessage);
            break;
        case Aura::Log::Level::Error:
            Aura::Log::GetLogger()->error(msg, tag, logMessage);
            break;
        case Aura::Log::Level::Critical:
            Aura::Log::GetLogger()->critical(msg, tag, logMessage);
            break;
        default:
            break;
        }
    }
}