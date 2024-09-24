#include "vevk_device.h"
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
            return device;
        }
    }

    VEVK_WARN("Not found suitable physical device of vulkan API in current device!! :-(");
    return nullptr;
}

}