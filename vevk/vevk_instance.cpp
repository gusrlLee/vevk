#include "vevk_instance.h"
#include "vevk.h"

namespace vevk {

    bool check_supported_extensions_by_instance(const char** extension_name_list, int extension_count) {
        std::vector<vk::ExtensionProperties> supported_extension_list = vk::enumerateInstanceExtensionProperties();
        bool is_found;

        for (int i = 0; i < extension_count; i++) {
            const char* extension_name = extension_name_list[i];
            is_found = false;

            for (vk::ExtensionProperties supported_extenion : supported_extension_list) {
                if (strcmp(extension_name, supported_extenion.extensionName) == 0) {
                    is_found = true;
                    break;
                }
            }

            if (!is_found) {
                VEVK_WARN("Not support extension:");
                VEVK_WARN(extension_name);
                return false;
            }
        }

        return true;
    }

    bool check_supported_layers_by_instance(const char** layer_name_list, int layer_count) {
        std::vector<vk::LayerProperties> supported_layer_list = vk::enumerateInstanceLayerProperties();

        bool is_found;
        for (int i = 0; i < layer_count; i++) {
            const char* layer_name =  layer_name_list[i];
            is_found = false;

            for (vk::LayerProperties supported_layer : supported_layer_list) {
                if (strcmp(layer_name, supported_layer.layerName) == 0) {
                    is_found = true;
                    break;
                }
            }

            if (!is_found) {
                VEVK_WARN("Not support layer");
                VEVK_WARN(layer_name);
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> get_required_extensions() {
        uint32_t glfw_extension_count = 0;
        const char** glfw_extension_list;

        glfw_extension_list = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
        std::vector<const char*> extension_list(glfw_extension_list, glfw_extension_list + glfw_extension_count);
#if __APPLE__
        extension_list.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

        if ( is_enable_validation_layer ) {
            extension_list.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extension_list;
    }

    vk::Instance create_instance(std::string application_name) {
        VEVK_INFO("Create vulkan instance!");
        uint32_t version = vk::enumerateInstanceVersion();

        // TODO - 변형 필요 
        vk::ApplicationInfo app_info = vk::ApplicationInfo(
            application_name.c_str(),
            VK_MAKE_VERSION(1, 0, 0),
            "VEVK Engine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_3
        );

        // NOTE - GLFW extensions
        std::vector<const char*> required_extensions = get_required_extensions();
        if (!check_supported_extensions_by_instance(required_extensions.data(), required_extensions.size())) {
            VEVK_WARN("Failed to create vulkan instance, due to not support extensions...");
            return nullptr;
        }

        // NOTE - Layer 
        std::vector<const char*> enabled_layer_list;
        if ( is_enable_validation_layer ) {
            enabled_layer_list.push_back("VK_LAYER_KHRONOS_validation");
        }

        if (!check_supported_layers_by_instance(enabled_layer_list.data(), enabled_layer_list.size())) {
            VEVK_WARN("Failed to create vulkan instance, due to layer...");
            return nullptr;
        }

        // NOTE = Instance create 
        vk::InstanceCreateInfo instance_create_info = vk::InstanceCreateInfo(
            vk::InstanceCreateFlags(),
            &app_info,
            static_cast<uint32_t>(enabled_layer_list.size()),
            enabled_layer_list.data(),
            static_cast<uint32_t>(required_extensions.size()),
            required_extensions.data()
        );

#if __APPLE__
        // NOTE - Because m1 chip appple device is used MotlenVK.
        instance_create_info.flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
#endif
        ResultCheck<vk::Instance> instance_temp = vk::createInstance(instance_create_info);
        if (!instance_temp.has_value()) {
            VEVK_ERROR("Failed to create vulkan instance :-(");
            std::exit(-1);
        }
        VEVK_INFO("Success to create vulkan instance! :-)");
        return instance_temp.value();
    }
}