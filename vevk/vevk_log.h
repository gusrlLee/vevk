#pragma once 
#include "vevk_pch.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace vevk {
    class Log {
        public:
            static void init();
            static std::shared_ptr<spdlog::logger>& Get() { return s_logger; }

            vk::DebugUtilsMessengerEXT make_debug_messenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dldi);
        private:
            static std::shared_ptr<spdlog::logger> s_logger;
    };
}

#define VEVK_LOG(...)    ::vevk::Log::Get()->trace(__VA_ARGS__)
#define VEVK_INFO(...)    ::vevk::Log::Get()->info(__VA_ARGS__)
#define VEVK_ERROR(...)    ::vevk::Log::Get()->error(__VA_ARGS__)
#define VEVK_WARN(...)    ::vevk::Log::Get()->warn(__VA_ARGS__)