#include "vevk_util_functions.h"
#include "vevk_core.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "[VALIDATION LAYER]: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

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
    if (gEnvConfig.bIsUsedValidationLayer)
    {
        requiredGlfwExtensionsList.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    if (gEnvConfig.userOS == VEVK_MACOS) 
    {
        requiredGlfwExtensionsList.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    }
    return requiredGlfwExtensionsList;
}

std::vector<const char*> vevkGetRequiredLayers()
{
    std::vector<const char*> requiredLayerList;
    if(gEnvConfig.bIsUsedValidationLayer)
    {
        requiredLayerList.push_back("VK_LAYER_KHRONOS_validation");
    }

    return requiredLayerList;
}

VkApplicationInfo vevkMakeApplicationInfo()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_3;
    appInfo.pApplicationName = "Vevk applifcation";
    appInfo.pEngineName = "Vevk enigne";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    return appInfo;
}

VkInstanceCreateInfo vevkMakeInstanceInfo()
{
    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    if (gEnvConfig.userOS == VEVK_MACOS) 
    {
        instanceInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }
    return instanceInfo;
}

VkDebugUtilsMessengerCreateInfoEXT vevkMakeDebugMessengerCreateInfo()
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; // Optional
    return createInfo;
}

VkResult vevkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void vevkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}