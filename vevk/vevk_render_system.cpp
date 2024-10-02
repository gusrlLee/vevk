#include "vevk_render_system.h"
#include "vevk_context.h"

namespace vevk {

void IRenderSystem::prepare(ref<Context> ctx) {
    // Connect 
    m_ctx = ctx;
    m_render_pass = m_ctx->create_basic_render_pass();

}

void IRenderSystem::destroy() {
    m_ctx->get_dispatch_table().destroyRenderPass(m_render_pass, nullptr);
}

}