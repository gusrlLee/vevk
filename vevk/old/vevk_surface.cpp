#include "vevk_surface.h"

namespace vevk {

vk::SurfaceKHR create_surface(GLFWwindow *window, vk::Instance instance) {
    VkSurfaceKHR raw_surface;
    if (glfwCreateWindowSurface(instance, window, nullptr, &raw_surface) != VK_SUCCESS) {
        VEVK_WARN("Failed to create surface :-(");
        return nullptr;
    }

    VEVK_INFO("Success to create surface! :-)");
    return raw_surface;
}

}