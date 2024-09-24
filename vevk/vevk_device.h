#pragma once 

#include "vevk_pch.h"

namespace vevk {

    bool check_requested_device_extensions_by_device(const vk::PhysicalDevice& target_device, const char** requested_device_extension_list, const uint32_t requested_device_extension_count);

    bool check_this_device_suitable(const vk::PhysicalDevice& target_device);

    vk::PhysicalDevice choose_physical_device(const vk::Instance& instance);
}