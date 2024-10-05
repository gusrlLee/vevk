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
    VEVK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &Instance));

    return true;
}

void VEVKContext::destroy()
{
    vkDestroyInstance(Instance, nullptr);
}
