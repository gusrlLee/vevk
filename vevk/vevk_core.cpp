#include "vevk_core.h"
#include "vevk_types.h"

static VEVKGfxContextCreateInfo* vevkGfxContextCreateInfo = nullptr;

void vevkInit() 
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    vevkGfxContextCreateInfo = new VEVKGfxContextCreateInfo();
}

void vevkHint(VEVK_HINT hint, uint32_t value)
{
    vevkGfxContextCreateInfo->userVulaknVersion = VK_VERSION_1_3; // default vulkan version 
    switch (hint) 
    {
        case VEVK_CONTEXT_VULKAN_API_VERSION:
            vevkGfxContextCreateInfo->userVulaknVersion = value;
            break; 
        case VEVK_USE_VALIDATION_LAYER:
            vevkGfxContextCreateInfo->bIsUsedValidationLayer = value == VEVK_TRUE ? VEVK_TRUE : VEVK_FALSE;
            if (value) {
                std::cout << "Heloo? " << std::endl;
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
        vevkGfxContextCreateInfo->pInstanceExtensionsNames.push_back(extensionName.c_str());
        break;

    case VEVK_CONTEXT_DEVICE_ADDITIONAL_EXTENSION:
        vevkGfxContextCreateInfo->pDeviceExtensionsNames.push_back(extensionName.c_str());
        break;
    
    default:
        break;
    }
}

void vevkTerminate() 
{
    delete vevkGfxContextCreateInfo;
    glfwTerminate();
}

VEVKGfxContext* vevkCreateGfxContext()
{
    return new VEVKGfxContext();
}

void vevkDestroyGfxContext(VEVKGfxContext* gfxContext) 
{
    delete gfxContext;
}