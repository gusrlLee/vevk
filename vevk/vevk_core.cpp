#include "vevk_core.h"
#include "vevk_types.h"
#include "vevk_context.h"
#include "vevk_log.h"

VEVKGlobalEnvironmentConfig gEnvConfig;
class VEVKContext* gContext = nullptr;

void vevkInit() 
{
    Log::init();
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    gContext = new VEVKContext();
}

void vevkHint(VEVK_HINT hint, uint32_t value)
{
    gEnvConfig.userVulaknVersion = VK_API_VERSION_1_3; // default vulkan version 
    switch (hint) 
    {
        case VEVK_CONTEXT_VULKAN_API_VERSION:
            gEnvConfig.userVulaknVersion = value;
            break; 
            
        case VEVK_USE_VALIDATION_LAYER:
            gEnvConfig.bIsUsedValidationLayer = value == VEVK_TRUE ? VEVK_TRUE : VEVK_FALSE;
            break;

        case VEVK_CONTEXT_OS_TYPE:
            switch (value)
            {
                case VEVK_WINDOW:
                    gEnvConfig.userOS = VEVK_WINDOW;
                    break;
                case VEVK_MACOS:
                    gEnvConfig.userOS = VEVK_MACOS;
                    break;
                case VEVK_LINUX:
                    gEnvConfig.userOS = VEVK_LINUX;
                    break;
                default:
                    std::runtime_error("Not yet support :-(");
                    break;
            }
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

bool vevkIsSetupDone()
{
    return gContext->init();
}

void vevkTerminate() 
{
    gContext->destroy();
    delete gContext;
    
    glfwTerminate();
}

