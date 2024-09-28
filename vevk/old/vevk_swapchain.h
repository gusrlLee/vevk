#pragma once 
#include "vevk_pch.h"
#include "vevk_types.h"
#include "vevk_context.h"

namespace vevk {
    class Swapchain {
        public:
            void prepare(Ptr<Context> ctx);
            void destroy();

            vkb::Swapchain get_swapchain() { return m_swapchain; }

        private:
            vkb::Swapchain m_swapchain;
    };
}