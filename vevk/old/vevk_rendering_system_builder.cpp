#include "vevk_rendering_system_builder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace vevk {

// SECTION - PUBLIC FUNCTIONS
RenderingSystemBuilder::RenderingSystemBuilder(Ptr<Context> ctx, Ptr<Swapchain> swapchain) 
    : m_ctx(ctx), m_swapchain(swapchain) { }

vk::Queue RenderingSystemBuilder::get_queue(vkb::QueueType request_queue_type) {
    auto queue = m_ctx->get_device().get_queue(request_queue_type);
    if (!queue.has_value()) {
        VEVK_ERROR("Failed to find queue! :-(");
        VEVK_ERROR(queue.error().message());
        return nullptr;
    }

    return queue.value();
}

vk::Queue RenderingSystemBuilder::get_graphics_queue() {
    auto graphics_queue = m_ctx->get_device().get_queue(vkb::QueueType::graphics);
    if (!graphics_queue.has_value()) {
        VEVK_ERROR("Failed to find graphics queue! :-(");
        VEVK_ERROR(graphics_queue.error().message());
        return nullptr;
    }

    return graphics_queue.value();
}

vk::Queue RenderingSystemBuilder::get_present_queue() {
    auto present_queue = m_ctx->get_device().get_queue(vkb::QueueType::present);
    if (!present_queue.has_value()) {
        VEVK_ERROR("Failed to find graphics queue! :-(");
        VEVK_ERROR(present_queue.error().message());
        return nullptr;
    }

    return present_queue.value();
}

// TODO - we need converting C format to C++ format
vk::RenderPass RenderingSystemBuilder::create_basic_render_pass() {
    VkAttachmentDescription color_attachment = {};
    color_attachment.format = m_swapchain->get_swapchain().image_format;
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

    VkRenderPass raw_render_pass;
    if (m_ctx->get_dispatch_table().createRenderPass(&render_pass_info, nullptr, &raw_render_pass) != VK_SUCCESS) {
        VEVK_ERROR("Failed to create render pass! :-(");
        return nullptr;
    }
    vk::RenderPass render_pass = raw_render_pass;
    return render_pass;
}

vk::PipelineLayout RenderingSystemBuilder::create_pipeline_layout() {
    VkPipelineLayoutCreateInfo pipeline_layout_info = {};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pushConstantRangeCount = 0;    

    VkPipelineLayout raw_pipeline_layout;
    if (m_ctx->get_dispatch_table().createPipelineLayout(&pipeline_layout_info, nullptr, &raw_pipeline_layout) != VK_SUCCESS) {
        VEVK_ERROR("Failed to create pipeline layout! :-(");
        return nullptr;
    }

    VEVK_INFO("Success to create pipeline layout! :-)");
    return raw_pipeline_layout;
}

// TODO - we need converting C format to C++ format
vk::Pipeline RenderingSystemBuilder::create_graphics_pipeline(vk::RenderPass &render_pass, vk::PipelineLayout &pipeline_layout, const char* vertex_shader_path, const char* fragment_shader_path) {
    auto vertex_shader_code = read_binary_shader_files(vertex_shader_path);
    auto fragment_shader_code = read_binary_shader_files(fragment_shader_path);

    vk::ShaderModule vertex_shader_module = create_shader_module(vertex_shader_code);
    vk::ShaderModule fragment_shader_module = create_shader_module(fragment_shader_code);

    if (vertex_shader_module == VK_NULL_HANDLE || fragment_shader_module == VK_NULL_HANDLE) {
        VEVK_ERROR("Failed to create shader module! check your shader file path.. :-(");
        return nullptr;
    }

    vk::PipelineShaderStageCreateInfo vertex_stage_create_info = vk::PipelineShaderStageCreateInfo(
        vk::PipelineShaderStageCreateFlags(),
        vk::ShaderStageFlagBits::eVertex,
        vertex_shader_module,
        "main"
    );

    vk::PipelineShaderStageCreateInfo fragment_stage_create_info = vk::PipelineShaderStageCreateInfo (
        vk::PipelineShaderStageCreateFlags(),
        vk::ShaderStageFlagBits::eFragment,
        fragment_shader_module,
        "main"
    );

    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_stage_create_info, fragment_stage_create_info };
    VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
    vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_info.vertexBindingDescriptionCount = 0;
    vertex_input_info.vertexAttributeDescriptionCount = 0;

    VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
    input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)m_swapchain->get_swapchain().extent.width;
    viewport.height = (float)m_swapchain->get_swapchain().extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = m_swapchain->get_swapchain().extent;

    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 1;
    viewport_state.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo color_blending = {};
    color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blending.logicOpEnable = VK_FALSE;
    color_blending.logicOp = VK_LOGIC_OP_COPY;
    color_blending.attachmentCount = 1;
    color_blending.pAttachments = &colorBlendAttachment;
    color_blending.blendConstants[0] = 0.0f;
    color_blending.blendConstants[1] = 0.0f;
    color_blending.blendConstants[2] = 0.0f;
    color_blending.blendConstants[3] = 0.0f;

    std::vector<VkDynamicState> dynamic_states;
    dynamic_states.push_back(VK_DYNAMIC_STATE_VIEWPORT);
    dynamic_states.push_back(VK_DYNAMIC_STATE_SCISSOR);

    VkPipelineDynamicStateCreateInfo dynamic_info = {};
    dynamic_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_info.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
    dynamic_info.pDynamicStates = dynamic_states.data();

    VkGraphicsPipelineCreateInfo pipeline_info = {};
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount = 2;
    pipeline_info.pStages = shader_stages;
    pipeline_info.pVertexInputState = &vertex_input_info;
    pipeline_info.pInputAssemblyState = &input_assembly;
    pipeline_info.pViewportState = &viewport_state;
    pipeline_info.pRasterizationState = &rasterizer;
    pipeline_info.pMultisampleState = &multisampling;
    pipeline_info.pColorBlendState = &color_blending;
    pipeline_info.pDynamicState = &dynamic_info;
    pipeline_info.layout = pipeline_layout;
    pipeline_info.renderPass = render_pass;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    VkPipeline raw_graphics_pipeline;
    if (m_ctx->get_dispatch_table().createGraphicsPipelines(VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &raw_graphics_pipeline) != VK_SUCCESS) {
        VEVK_ERROR("Failed to create graphics pipeline! :-(");
        return nullptr;
    }

    m_ctx->get_dispatch_table().destroyShaderModule(vertex_shader_module, nullptr);
    m_ctx->get_dispatch_table().destroyShaderModule(fragment_shader_module, nullptr);

    VEVK_INFO("Success to create graphics pipeline! :-)");
    return raw_graphics_pipeline;
}

vk::Framebuffer RenderingSystemBuilder::create_frame_buffer() {
    
}

// SECTION - PRIVATE FUNCTIONS
std::vector<char> RenderingSystemBuilder::read_binary_shader_files(const std::string &filename) {
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

vk::ShaderModule RenderingSystemBuilder::create_shader_module(const std::vector<char> shader_code) {
    VkShaderModuleCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = shader_code.size();
    create_info.pCode = reinterpret_cast<const uint32_t*>(shader_code.data());

    VkShaderModule shader_module;
    if (m_ctx->get_dispatch_table().createShaderModule(&create_info, nullptr, &shader_module) != VK_SUCCESS) {
        return VK_NULL_HANDLE; // failed to create shader module
    }

    return shader_module;
}

}