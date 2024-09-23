#pragma once 
#include <iostream>
#include <spdlog/spdlog.h>

namespace vevk {
    class Log {
        public:
            static void init();
            static std::shared_ptr<spdlog::logger>& Get() { return s_logger; }
        
        private:
            static std::shared_ptr<spdlog::logger> s_logger;

    };
}

#define VEVK_LOG(...)    ::vevk::Log::Get()->trace(__VA_ARGS__)
#define VEVK_INFO(...)    ::vevk::Log::Get()->info(__VA_ARGS__)
#define VEVK_ERROR(...)    ::vevk::Log::Get()->error(__VA_ARGS__)