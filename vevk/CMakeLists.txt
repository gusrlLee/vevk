cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
find_package(Vulkan REQUIRED)

add_library(VEVK_LIB 
    vevk_pch.h
    vevk.h
    vevk.cpp

    vevk_core.h
    vevk_core.cpp

    vevk_window.h
    vevk_window.cpp

    vevk_gfx_context.h
    vevk_gfx_context.cpp

    vevk_util_functions.h
    vevk_util_functions.cpp
)

target_link_libraries(VEVK_LIB Vulkan::Vulkan)
target_link_libraries(VEVK_LIB glfw)
target_link_libraries(VEVK_LIB spdlog::spdlog_header_only)
target_link_libraries(VEVK_LIB vk-bootstrap::vk-bootstrap)