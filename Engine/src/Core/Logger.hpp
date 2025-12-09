#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/pattern_formatter.h>

namespace GameEngine
{
    class Logger
    {
    public:
        static Logger& get() 
        {
            static Logger logger;
            return logger;
        }
        std::shared_ptr<spdlog::async_logger> coreLogger;
    private:
        void init();
        Logger() { init(); };
        ~Logger() = default;
    };
}

#define LOG_TRACE(...) ::GameEngine::Logger::get().coreLogger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace ,__VA_ARGS__);
#define LOG_INFO(...) ::GameEngine::Logger::get().coreLogger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info ,__VA_ARGS__);
#define LOG_WARN(...) ::GameEngine::Logger::get().coreLogger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn ,__VA_ARGS__);
#define LOG_ERROR(...) ::GameEngine::Logger::get().coreLogger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err ,__VA_ARGS__);
#define LOG_CRITICAL(...) ::GameEngine::Logger::get().coreLogger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical ,__VA_ARGS__);