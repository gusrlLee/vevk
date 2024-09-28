cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
find_package(Vulkan REQUIRED)

add_library(VEVK_LIB 
    vevk_pch.h
    vevk_pch.cpp
    
    vevk.h
    vevk.cpp

    vevk_log.h
    vevk_log.cpp
)

target_link_libraries(VEVK_LIB Vulkan::Vulkan)
target_link_libraries(VEVK_LIB glfw)
target_link_libraries(VEVK_LIB spdlog::spdlog_header_only)
target_link_libraries(VEVK_LIB vk-bootstrap::vk-bootstrap)