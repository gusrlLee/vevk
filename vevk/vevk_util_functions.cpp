#include "vevk_util_functions.h"

bool vevkCheckSupportedExtensionsByInstance(const char** extensionNameList, int extensionCount)
{
    uint32_t supportedExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, nullptr);
    std::vector<VkExtensionProperties> supportedExtensionList(supportedExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, supportedExtensionList.data());

    bool bIsFound = false;
    for (int i = 0; i < extensionCount; i++)  
    {
        const char* extensionName = extensionNameList[i];
        bIsFound = false;

        for (VkExtensionProperties supportedExtension : supportedExtensionList) 
        {
            if (strcmp(extensionName, supportedExtension.extensionName) == 0)
            {
                bIsFound = true;
                break;
            }
        }
        if (!bIsFound)
        {
            return false;
        }
    }

    return true;
}

void vevkPrintSupportedExtensionsByInstance()
{
    uint32_t supportedExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, nullptr);
    std::vector<VkExtensionProperties> supportedExtensionList(supportedExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, supportedExtensionList.data());

    std::cout << "Supported extensions list : " << std::endl;
    for (VkExtensionProperties supportedExtension : supportedExtensionList) 
    {
        std::cout << "\t" << supportedExtension.extensionName << std::endl;  
    }
}

bool vevkCheckSupportedLayersByInstance(const char** layerNameList, int layerCount)
{
    uint32_t supportedLayerCount = 0;
    vkEnumerateInstanceLayerProperties(&supportedLayerCount, nullptr);
    std::vector<VkLayerProperties> supportedLayerList(supportedLayerCount);
    vkEnumerateInstanceLayerProperties(&supportedLayerCount, supportedLayerList.data());

    bool bIsFound = false;
    for (int i = 0; i < layerCount; i++) 
    {
        const char* layerName = layerNameList[i];

        bIsFound = false;
        for (VkLayerProperties supportedLayer : supportedLayerList)
        {
            if (strcmp(layerName, supportedLayer.layerName) == 0)
            {
                bIsFound = true;
                break;
            }
        }
        if (!bIsFound)
        {
            return false;
        }
    }

    return true;
}

void vevkPrintSupportedLayersByInstance()
{
    uint32_t supportedLayerCount = 0;
    vkEnumerateInstanceLayerProperties(&supportedLayerCount, nullptr);
    std::vector<VkLayerProperties> supportedLayerList(supportedLayerCount);
    vkEnumerateInstanceLayerProperties(&supportedLayerCount, supportedLayerList.data());

    std::cout << "Supported layer list : " << std::endl;
    for (VkLayerProperties supportedLayer : supportedLayerList)
    {
        std::cout << "\t" << supportedLayer.layerName << std::endl;
    }
}

std::vector<const char*> vevkGetRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExntensionList;
    glfwExntensionList = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> requiredGlfwExtensionsList(glfwExntensionList, glfwExntensionList + glfwExtensionCount);
    return requiredGlfwExtensionsList;
}

VkApplicationInfo vevkMakeApplicationInfo()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    return appInfo;
}

VkInstanceCreateInfo vevkMakeInstanceInfo()
{
    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return instanceInfo;
}