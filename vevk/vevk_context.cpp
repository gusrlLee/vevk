#include "vevk_context.h"

namespace vevk {
    void Context::prepare(GLFWwindow* window) {
        m_target_window = window;


        // SECTION - Init instance
        vkb::InstanceBuilder instance_builder;
        auto instance_ret = instance_builder
            .request_validation_layers()
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
        if (glfwCreateWindowSurface(m_instance, m_target_window, nullptr, &raw_surface) != VK_SUCCESS) {
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

        // SECTION - Init swapchain
        vkb::SwapchainBuilder swapchain_builder{ m_device };
        auto swap_ret = swapchain_builder
            .set_old_swapchain(m_swapchain)
            .build();

        if (!swap_ret) {
            VEVK_ERROR("Failed to create swapchain! :-(");
            VEVK_ERROR(swap_ret.error().message());
        }
        vkb::destroy_swapchain(m_swapchain);

        VEVK_INFO("Sucess to create swapchain! :-)");
        m_swapchain = swap_ret.value();
    }

    void Context::destroy() {
        vkb::destroy_swapchain(m_swapchain);
        vkb::destroy_surface(m_instance, m_surface);
        vkb::destroy_device(m_device);
        vkb::destroy_instance(m_instance);
    }

    VkRenderPass Context::create_basic_render_pass() {
        VkAttachmentDescription color_attachment = {};
        color_attachment.format = m_swapchain.image_format;
        color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
        color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference color_attachment_ref = {};
        color_attachment_ref.attachment = 0;
        color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &color_attachment_ref;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo render_pass_info = {};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        render_pass_info.attachmentCount = 1;
        render_pass_info.pAttachments = &color_attachment;
        render_pass_info.subpassCount = 1;
        render_pass_info.pSubpasses = &subpass;
        render_pass_info.dependencyCount = 1;
        render_pass_info.pDependencies = &dependency;

        VkRenderPass render_pass;
        if (m_disp_table.createRenderPass(&render_pass_info, nullptr, &render_pass) != VK_SUCCESS) {
            VEVK_ERROR("Failed to create render pass! :-(");
            return nullptr;
        }
        return render_pass;
    }

    VkShaderModule Context::create_shader_module(const std::vector<char> shader_code) {
        VkShaderModuleCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = shader_code.size();
        create_info.pCode = reinterpret_cast<const uint32_t*>(shader_code.data());

        VkShaderModule shader_module;
        if (m_disp_table.createShaderModule(&create_info, nullptr, &shader_module) != VK_SUCCESS) {
            return VK_NULL_HANDLE; // failed to create shader module
        }

        return shader_module;
    }

    std::vector<char> Context::read_binary_shader_files(const std::string &filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t file_size = (size_t)file.tellg();
        std::vector<char> buffer(file_size);

        file.seekg(0);
        file.read(buffer.data(), static_cast<std::streamsize>(file_size));

        file.close();

        return buffer;
    }
}