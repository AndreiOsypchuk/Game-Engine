#pragma once
#include <memory>
#define SPDLOG_COMPILED_LIB
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
namespace GE
{
    class Logger
    {
        public:
            Logger() = delete;

            static void Init();

            static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger; }
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;

    };

}
#define GE_CORE_TRACE(...)              ::GE::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#define GE_CORE_INFO(...)               ::GE::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define GE_CORE_WARN(...)               ::GE::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define GE_CORE_ERR(...)                ::GE::Logger::GetCoreLogger()->error(__VA_ARGS__);

#define GE_TRACE(...)                   ::GE::Logger::GetClientLogger()->trace(__VA_ARGS__);
#define GE_INFO(...)                    ::GE::Logger::GetClientLogger()->info(__VA_ARGS__);
#define GE_WARN(...)                    ::GE::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define GE_ERR(...)                     ::GE::Logger::GetClientLogger()->error(__VA_ARGS__);