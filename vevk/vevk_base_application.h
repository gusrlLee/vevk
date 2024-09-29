#pragma once 

#include "vevk_pch.h"

namespace vevk {
    class IBaseApplication {
    public:
        void prepare();
        void destroy();
        
    private:
        GLFWwindow* m_window;

    };
}