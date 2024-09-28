cmake_minimum_required(VERSION 3.5)
project(Tracer)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_subdirectory(vender)
add_subdirectory(vevk)

# add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME} test.cpp)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} vk-bootstrap::vk-bootstrap)
# target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} glfw)
# target_link_libraries(${PROJECT_NAME} VEVK_LIB)

