#pragma once 
#include "vevk_pch.h"

// SECTION - all of context in vulkan api
class VEVKContext {
    public:
        bool init();
        void destroy();

        bool bIsReady = false;

        VkInstance Instance;
        VkDebugUtilsMessengerEXT DebugUtils = VK_NULL_HANDLE;
};