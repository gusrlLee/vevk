#pragma once 
#include "vevk_pch.h"
#include "vevk.h"

namespace vevk {
    class Context {
        public:
            void prepare(GLFWwindow* window);
            void destroy();

            vkb::Instance get_instance() { return m_instance; }
            vkb::Device get_device() { return m_device; }
            VkSurfaceKHR get_surface() { return m_surface; }

            vkb::DispatchTable get_dispatch_table() { return m_disp_table; }

        private:
            vkb::Instance m_instance;
            vkb::InstanceDispatchTable m_inst_disp_table;

            vkb::Device m_device;
            vkb::DispatchTable m_disp_table;

            VkSurfaceKHR m_surface;
    };
}