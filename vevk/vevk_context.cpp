#include "vevk_context.h"

namespace vevk {
    void Context::prepare(GLFWwindow* window) {
        
        // SECTION - Init instance
        vkb::InstanceBuilder instance_builder;
        auto instance_ret = instance_builder
            .request_validation_layers(is_enable_validation_layer)
            .use_default_debug_messenger()
            .build();

        if (!instance_ret) {
            VEVK_ERROR("Failed to create instance! :-(");
        }
        VEVK_INFO("Success to create instance! :-)");

        m_instance = instance_ret.value();
        m_inst_disp_table = m_instance.make_table();

        vkb::PhysicalDeviceSelector physical_device_selector{m_instance};

        // SECTION - Init surface
        VkSurfaceKHR raw_surface;
        if (glfwCreateWindowSurface(m_instance, window, nullptr, &raw_surface) != VK_SUCCESS) {
            VEVK_ERROR("Failed to create surface! :-(");
        }
        m_surface = raw_surface;
        VEVK_INFO("Success to create surface! :-)");

        // SECTION - Init device
        auto physical_device_ret = physical_device_selector
            .set_surface(m_surface)
            .set_minimum_version(1, 1)
            .select();

        if (!physical_device_ret) {
            VEVK_ERROR("Not support vulkan API for current device surface! :-(");
        }

        vkb::DeviceBuilder device_builder{physical_device_ret.value()};
        auto dev_ret = device_builder.build();
        if (!dev_ret) {
            VEVK_ERROR("Failed to create vulkan logical device! :-(");
            VEVK_ERROR(dev_ret.error().message());
        }
        m_device = dev_ret.value();
        VEVK_INFO("Success to create device! :-)");
        m_disp_table = m_device.make_table();
    }

    void Context::destroy() {
        vkb::destroy_surface(m_instance, m_surface);
        vkb::destroy_device(m_device);
        vkb::destroy_instance(m_instance);
    }
}