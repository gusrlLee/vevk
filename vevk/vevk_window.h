#pragma once 
#include "vevk_pch.h"

namespace vevk {
/// @brief Create main window for program.
/// @param window_width window width size 
/// @param window_height window height size 
/// @param window_title window title name
/// @return GLFWwindow*
GLFWwindow* create_main_window(uint32_t window_width, uint32_t window_height, std::string window_title);

/// @brief  Destory glfw window
/// @param window used main window
void destroy_main_window(GLFWwindow* window);

}