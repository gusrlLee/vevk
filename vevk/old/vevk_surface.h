#pragma once 
#include "vevk_pch.h"

namespace vevk {
    
    vk::SurfaceKHR create_surface(GLFWwindow* window, vk::Instance instance);
}