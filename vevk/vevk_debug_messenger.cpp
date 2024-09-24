#include "vevk_debug_messenger.h"

namespace vevk {
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "[VALIDATION_LAYER_ERROR]: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

vk::DebugUtilsMessengerEXT make_debug_messenger(vk::Instance &instance, vk::DispatchLoaderDynamic &dldi)
{
    vk::DebugUtilsMessengerCreateInfoEXT create_info = vk::DebugUtilsMessengerCreateInfoEXT(
        vk::DebugUtilsMessengerCreateFlagsEXT(),
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
        debug_callback,
        nullptr
    );

    ResultCheck<vk::DebugUtilsMessengerEXT> messenger = instance.createDebugUtilsMessengerEXT(create_info, nullptr, dldi);
    VkDebugUtilsMessengerEXT handle = messenger.value();

    if ( !messenger.has_value() ) {
        VEVK_WARN("Failed to create debug messenger!... ");
        return nullptr;
    }

    VEVK_INFO("Success to create debug messenger! :-)");
    return messenger.value();
}

}