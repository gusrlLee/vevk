#pragma once 

#include "vevk_pch.h"
#include "vevk_types.h"

namespace vevk {
    class Context;
    class Swapchain;

    class IBaseApplication {
    public:
        void prepare();
        void destroy();

        void run();
        
    private:
        GLFWwindow* m_window;
        ref<Context> m_ctx;
        ref<Swapchain> m_swapchain;
    };
}