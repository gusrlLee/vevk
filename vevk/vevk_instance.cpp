#include "vevk_instance.h"

namespace vevk {

vk::Instance create_instance(std::string application_name) {
    VEVK_INFO("Create vulkan instance!");
    uint32_t version = vk::enumerateInstanceVersion();

    vk::ApplicationInfo app_info = vk::ApplicationInfo(
        application_name.c_str(),
        VK_MAKE_VERSION(1, 0, 0),
        "VEVK Engine",
        VK_MAKE_VERSION(1, 0, 0),
        VK_API_VERSION_1_3
    );

    //NOTE - GLFW extensions
    uint32_t glfw_extensions_count = 0;
    const char** glfw_extensions;

    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extensions_count); 

    std::vector<const char*> required_extensions;
    for (uint32_t i = 0; i < glfw_extensions_count; i++) {
        required_extensions.push_back(glfw_extensions[i]);
    }

#if __APPLE__
    required_extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    //NOTE - Layer 
    uint32_t enabled_layer_count = 0;
    const char** enable_layers = nullptr;


    //NOTE = Instance create 
    vk::InstanceCreateInfo instance_create_info = vk::InstanceCreateInfo(
        vk::InstanceCreateFlags(),
        &app_info,
        glfw_extensions_count,
        required_extensions.data(),
        enabled_layer_count,
        enable_layers
    );

#if __APPLE__
    //NOTE - Because m1 chip appple device is used MotlenVK.
    instance_create_info.flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
#endif

    ResultCheck<vk::Instance> instance_temp = vk::createInstance(instance_create_info);
    if (!instance_temp.has_value()) {
        VEVK_ERROR("Failed to create vulkan instance.. :-(");
        std::exit(-1);
    }

    return instance_temp.value();
}


}