#pragma once 
#include "vevk_pch.h"
#include "vevk_types.h"

namespace vevk {

vk::DebugUtilsMessengerEXT make_debug_messenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dldi);

}