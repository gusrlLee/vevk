#include "vevk/vevk.h"
#include "vevk/vevk_context.h"
#include "vevk/vevk_swapchain.h"
#include "vevk/vevk_rendering_system_builder.h"

int main() {
    vevk::init();
    vevk::hint(vevk::VEVK_VALIDATION_LAYER, vevk::VEVK_USE_VALIDATION_LAYER);

    GLFWwindow* window = vevk::create_main_window(1280, 720, "Test");
    auto gfx_ctx = vevk::make<vevk::Context>();
    auto gfx_swapchain = vevk::make<vevk::Swapchain>();

    gfx_ctx->prepare(window);
    gfx_swapchain->prepare(gfx_ctx);

    auto rendering_system_builder = vevk::make<vevk::RenderingSystemBuilder>(gfx_ctx, gfx_swapchain);
    // vk::Queue graphics_queue = rendering_system_builder->get_queue(vkb::QueueType::graphics);
    vk::Queue present_queue = rendering_system_builder->get_queue(vkb::QueueType::present);
    vk::Queue compute_queue = rendering_system_builder->get_queue(vkb::QueueType::graphics);
    vk::Queue compute_queue2 = rendering_system_builder->get_queue(vkb::QueueType::compute);

    vk::RenderPass render_pass = rendering_system_builder->create_basic_render_pass();
    vk::PipelineLayout pipeline_layout = rendering_system_builder->create_pipeline_layout();
    vk::Pipeline graphics_pipelien = rendering_system_builder->create_graphics_pipeline(render_pass, pipeline_layout, "../Shader/triangle_vert.spv", "../Shader/triangle_frag.spv");

    // SECTION - we do 

    gfx_ctx->get_dispatch_table().destroyPipeline(graphics_pipelien, nullptr);
    gfx_ctx->get_dispatch_table().destroyPipelineLayout(pipeline_layout, nullptr);
    gfx_ctx->get_dispatch_table().destroyRenderPass(render_pass, nullptr);
    gfx_swapchain->destroy();
    gfx_ctx->destroy();

    vevk::destroy_main_window(window);
    vevk::terminate();

    return EXIT_SUCCESS;
}