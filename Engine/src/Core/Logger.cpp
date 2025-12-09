#include "Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

namespace GameEngine
{
    void Logger::init()
    {
        spdlog::init_thread_pool(8192, 1);
        auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/log.txt", 0, 0);
        std::vector<spdlog::sink_ptr> sinks{ stdout_sink, daily_sink };
        coreLogger = std::make_shared<spdlog::async_logger>("Engine", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        coreLogger->set_level(spdlog::level::trace);
        spdlog::register_logger(coreLogger);
    }
}