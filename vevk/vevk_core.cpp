#include "vevk_core.h"
#include "vevk_types.h"

void vevkInit() 
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void vevkHint(VEVK_HINT hint, uint32_t value)
{
    gEnvConfig.userVulaknVersion = VK_VERSION_1_3; // default vulkan version 
    switch (hint) 
    {
        case VEVK_CONTEXT_VULKAN_API_VERSION:
            gEnvConfig.userVulaknVersion = value;
            break; 
            
        case VEVK_USE_VALIDATION_LAYER:
            gEnvConfig.bIsUsedValidationLayer = value == VEVK_TRUE ? VEVK_TRUE : VEVK_FALSE;
            break;

        default:
            break;
    };
}

void vevkHint(VEVK_HINT hint, std::string extensionName)
{
    switch (hint)
    {
    case VEVK_CONTEXT_INSTANCE_ADDITIONAL_EXTENSION:
        break;

    case VEVK_CONTEXT_DEVICE_ADDITIONAL_EXTENSION:
        break;
    
    default:
        break;
    }
}

void vevkTerminate() 
{
    glfwTerminate();
}

