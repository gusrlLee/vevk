#pragma once 
#include "vevk_pch.h"
#include <iostream>
#include <spdlog/spdlog.h>

class Log {
    public:
        static void init();
        static std::shared_ptr<spdlog::logger>& get() { return s_logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_logger;
};

#define VEVK_LOG(...)        ::Log::get()->trace(__VA_ARGS__)
#define VEVK_INFO(...)       ::Log::get()->info(__VA_ARGS__)
#define VEVK_ERROR(...)      ::Log::get()->error(__VA_ARGS__)
#define VEVK_WARN(...)       ::Log::get()->warn(__VA_ARGS__)

#define VEVK_CHECK(x)                                                   \
    do {                                                                \
        VkResult err = x;                                               \
        if (err) {                                                      \
            std::cout << "Found error : " << err << std::endl;          \
            abort();                                                    \
        }                                                               \
    } while (0)