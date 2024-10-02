#pragma once 
#include "vevk_pch.h"
#include "vevk_types.h"

namespace vevk {
    class Context;

    typedef struct RenderSystemCreateInfo {

    } RenderSystemCreateInfo;

    class IRenderSystem {
        public:
            void prepare(ref<Context> ctx);
            void destroy();

            void draw();

        private:
            ref<Context> m_ctx;
            VkRenderPass m_render_pass;
    };
}