#include "vevk_swapchain.h" 

namespace vevk {
    void Swapchain::prepare(Ptr<Context> ctx) {
        vkb::SwapchainBuilder swapchain_builder{ ctx->get_device() };
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

    void Swapchain::destroy() {
        vkb::destroy_swapchain(m_swapchain);
    }
}