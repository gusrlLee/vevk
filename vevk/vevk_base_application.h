#pragma once 

#include "vevk_pch.h"

namespace vevk {
    class IBaseApplication {
    public:
        void prepare();
        void destroy();
        
    private:



        GLFWwindow* m_window;
        vkb::Instance m_instance;
        vkb::InstanceDispatchTable m_instance_dispatch_table;
        VkSurfaceKHR m_surface;
        vkb::Device m_device;
        vkb::DispatchTable m_dispatch_table;
        vkb::Swapchain m_swapchain;
    };
}