#include "pch.h"
#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace GE
{
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger = nullptr;
    std::shared_ptr<spdlog::logger> Logger::s_ClientLogger = nullptr;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%n]%$ %v");
        s_CoreLogger = spdlog::stdout_color_mt("THE_ENGINE");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
        s_ClientLogger->set_level(spdlog::level::trace);
        
    }
}