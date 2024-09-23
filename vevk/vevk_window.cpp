#include "vevk_window.h"

namespace vevk {

GLFWwindow* create_main_window(uint32_t window_width, uint32_t window_height, std::string window_title) {
    VEVK_INFO("create main window...");
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
    if (!window) {
        VEVK_ERROR("Failed to create main window! try again!");
        glfwTerminate();
        std::exit(-1);
    }

    return window;
}   

void destroy_main_window(GLFWwindow* window) {
    VEVK_INFO("destroy main window");
    glfwDestroyWindow(window);
}

}