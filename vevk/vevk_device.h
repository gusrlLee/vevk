#pragma once 

#include "vevk_pch.h"

namespace vevk {

    // SECTION - Physical Device 
    bool check_requested_device_extensions_by_device(const vk::PhysicalDevice& target_device, const char** requested_device_extension_list, const uint32_t requested_device_extension_count);

    bool check_this_device_suitable(const vk::PhysicalDevice& target_device);

    vk::PhysicalDevice choose_physical_device(const vk::Instance& instance);

    // SECTION - Logical Device

    uint32_t find_queue_family_index(vk::PhysicalDevice target_physical_device, vk::QueueFlags requested_queue_type);

    vk::Device create_logical_device(vk::PhysicalDevice physical_device);
}