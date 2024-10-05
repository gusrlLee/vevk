#include "vevk_context.h"
#include "vevk_core.h"
#include "vevk_log.h"
#include "vevk_util_functions.h"

bool VEVKContext::init()
{
    VkApplicationInfo appInfo = vevkMakeApplicationInfo();
    appInfo.apiVersion = gEnvConfig.userVulaknVersion;

    std::vector<const char*> glfwExtensionList = vevkGetRequiredExtensions();
    std::vector<const char*> layerList = vevkGetRequiredLayers();

    if(!vevkCheckSupportedExtensionsByInstance(glfwExtensionList.data(), glfwExtensionList.size()))
    {
        return false;
    }

    if (!vevkCheckSupportedLayersByInstance(layerList.data(), layerList.size()))
    {
        return false;
    }
    
    VkInstanceCreateInfo instanceInfo = vevkMakeInstanceInfo();
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensionList.size());
    instanceInfo.ppEnabledExtensionNames = glfwExtensionList.data();
    instanceInfo.enabledLayerCount = static_cast<uint32_t>(layerList.size());
    instanceInfo.ppEnabledLayerNames = layerList.data();
    
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = vevkMakeDebugMessengerCreateInfo();
    if (gEnvConfig.bIsUsedValidationLayer)
    {
        instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    }

    VEVK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &Instance));

    if (gEnvConfig.bIsUsedValidationLayer)
    {
        VEVK_CHECK(vevkCreateDebugUtilsMessengerEXT(Instance, &debugCreateInfo, nullptr, &DebugUtils));
    }


    return true;
}

void VEVKContext::destroy()
{
    if (gEnvConfig.bIsUsedValidationLayer)
    {
        vevkDestroyDebugUtilsMessengerEXT(Instance, DebugUtils, nullptr);
    }
    vkDestroyInstance(Instance, nullptr);
}
