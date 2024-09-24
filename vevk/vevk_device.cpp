#include "vevk_device.h"
#include "vevk_instance.h"
#include "vevk.h"
#include <string>
namespace vevk {

bool check_requested_device_extensions_by_device(const vk::PhysicalDevice &target_device, const char **requested_device_extension_list, const uint32_t requested_device_extension_count) {
    std::vector<vk::ExtensionProperties> device_extensions = target_device.enumerateDeviceExtensionProperties();

    for (uint32_t i = 0; i < requested_device_extension_count; i++) {
        bool is_supported = false;
        for (vk::ExtensionProperties& extension : device_extensions) {
            std::string extension_name = extension.extensionName;
            if (!extension_name.compare(requested_device_extension_list[i])) {
                is_supported = true;
                break;
            }
        }

        if (!is_supported) {
            return false;
        }
    }
    return true;
}

bool check_this_device_suitable(const vk::PhysicalDevice &target_device) {
    std::vector<const char*> request_device_extension_list;
    request_device_extension_list.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

    if (!check_requested_device_extensions_by_device(target_device, request_device_extension_list.data(), request_device_extension_list.size())) {
        return false;
    }

    return true;
}

vk::PhysicalDevice choose_physical_device(const vk::Instance& instance) {
    std::vector<vk::PhysicalDevice> available_devices_in_computer = instance.enumeratePhysicalDevices();

    for (vk::PhysicalDevice device : available_devices_in_computer) {
        if (check_this_device_suitable(device)) {
            VEVK_INFO("Success to select physical device! :-)");
            return device;
        }
    }

    VEVK_WARN("Not found suitable physical device of vulkan API in current device!! :-(");
    return nullptr;
}

uint32_t find_queue_family_index(vk::PhysicalDevice target_physical_device, vk::QueueFlags requested_queue_type) {
    std::vector<vk::QueueFamilyProperties> queue_families = target_physical_device.getQueueFamilyProperties();
    for (uint32_t i = 0; i < queue_families.size(); i++) {
        vk::QueueFamilyProperties queue_family  = queue_families[i];
        if (queue_family.queueFlags & requested_queue_type) {
            return i;
        }
    }

    VEVK_WARN("Not found queue family!");
    return UINT32_MAX;
}

vk::Device create_logical_device(vk::PhysicalDevice physical_device) {  
    uint32_t graphics_queue_index = find_queue_family_index(physical_device, vk::QueueFlagBits::eGraphics);
    float queue_priority = 1.0f;

    vk::DeviceQueueCreateInfo queue_create_info = vk::DeviceQueueCreateInfo(
        vk::DeviceQueueCreateFlags(),
        graphics_queue_index,
        1, 
        &queue_priority
    );

    vk::PhysicalDeviceFeatures device_features = vk::PhysicalDeviceFeatures();
    
    std::vector<const char*> enabled_layer_list;
    if ( is_enable_validation_layer )
        enabled_layer_list.push_back("VK_LAYER_KHRONOS_validation");
    
    std::vector<const char*> device_extenions_list;
    device_extenions_list.push_back("VK_KHR_portability_subset");

    vk::DeviceCreateInfo device_create_info = vk::DeviceCreateInfo(
        vk::DeviceCreateFlags(),
        1,
        &queue_create_info,
        static_cast<uint32_t>(enabled_layer_list.size()),
        enabled_layer_list.data(),
        static_cast<uint32_t>(device_extenions_list.size()),
        device_extenions_list.data(),
        &device_features
    );

    ResultCheck<vk::Device> device = physical_device.createDevice(device_create_info);
    if (!device.has_value()) {
        VEVK_WARN("Failed to create logical device by using selected physical device!... :-(");
        return nullptr;
    }

    VEVK_INFO("Success to create logical device by using selected physical device! :-)");
    return device.value();
}


}