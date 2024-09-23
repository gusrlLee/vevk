#include "vevk.h"

namespace vevk {
void init() {
    Log::init();
    VEVK_INFO("Start initialization!");

    // for GLFW library initializaiton
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // for use vulkan API 
}

void terminate() {
    glfwTerminate();
    VEVK_INFO("Bye!");
}

}

