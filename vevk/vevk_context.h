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

            VkShaderModule create_shader_module(const std::vector<char> shader_code);
            VkRenderPass create_basic_render_pass();

        private:
            std::vector<char> read_binary_shader_files(const std::string &filename);

            GLFWwindow* m_target_window;
            vkb::Instance m_instance;
            vkb::InstanceDispatchTable m_inst_disp_table;

            vkb::Device m_device;
            vkb::DispatchTable m_disp_table;

            VkSurfaceKHR m_surface;
            vkb::Swapchain m_swapchain;
    };
}