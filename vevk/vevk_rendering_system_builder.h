#pragma once 
#include "vevk_pch.h"
#include "vevk_types.h"
#include "vevk_context.h"
#include "vevk_swapchain.h"

namespace vevk {
    class RenderingSystemBuilder {
        public:
            RenderingSystemBuilder(Ptr<Context> ctx, Ptr<Swapchain> swapchain);
            ~RenderingSystemBuilder() {}

            vk::Queue get_queue(vkb::QueueType request_queue_type);
            vk::Queue get_graphics_queue();
            vk::Queue get_present_queue();


            vk::RenderPass create_basic_render_pass();
            vk::PipelineLayout create_pipeline_layout();
            vk::Pipeline create_graphics_pipeline(vk::RenderPass &render_pass, vk::PipelineLayout &pipeline_layout, const char* vertex_shader_path, const char* fragment_shader_path);

            vk::Framebuffer create_frame_buffer();
        private:
            std::vector<char> read_binary_shader_files(const std::string& filename);
            vk::ShaderModule create_shader_module(const std::vector<char> shader_code);

            Ptr<Context> m_ctx;
            Ptr<Swapchain> m_swapchain;

    };
}