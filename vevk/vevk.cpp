#include "vevk.h"

namespace vevk {
    void init() 
    {
        vevk::Log::init();
        VEVK_INFO("Hello vevk :-)");
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    void terminate() 
    {
        glfwTerminate();
    }
}