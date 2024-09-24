cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
find_package(Vulkan REQUIRED)

add_library(VEVK_LIB 
    vevk_types.h    
    vevk_pch.h
    
    vevk.h
    vevk.cpp
    
    vevk_context.h
    vevk_context.cpp

    vevk_window.h
    vevk_window.cpp

    vevk_log.h
    vevk_log.cpp

    vevk_instance.h
    vevk_instance.cpp

    vevk_application.h
    vevk_application.cpp

    vevk_debug_messenger.h
    vevk_debug_messenger.cpp

    vevk_device.h
    vevk_device.cpp
)

target_link_libraries(VEVK_LIB Vulkan::Vulkan)
target_link_libraries(VEVK_LIB glfw)
target_link_libraries(VEVK_LIB spdlog::spdlog_header_only)
