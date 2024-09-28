#include "vevk.h"

namespace vevk {

bool is_enable_validation_layer = false;

void init() {
    Log::init();
    VEVK_INFO("Start initialization!");

    // for GLFW library initializaiton
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // for use vulkan API 
}

void hint(Features feature, Options opt) {
    switch (feature) {
        case VEVK_VALIDATION_LAYER:
            switch (opt) {
                case VEVK_NO_USE_VALIDATION_LAYER: 
                    is_enable_validation_layer = false;
                    break;
                case VEVK_USE_VALIDATION_LAYER:
                    is_enable_validation_layer = true;
                    break;
                default:
                    is_enable_validation_layer = true;
                    break;
            }
            break;

        default:
            break;
    }
}

void terminate() {
    glfwTerminate();
    VEVK_INFO("Bye! :-)");
}

}

