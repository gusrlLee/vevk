#pragma once 
#include "vevk_pch.h"

namespace vevk {
    typedef struct ContextCreateInfo {
        GLFWwindow* window;
        
    } ContextCreateInfo;

    class Context {
        public:
            void prepare();
            void destroy();

        private:
            vk::Instance m_vk_instance;
            vk::PhysicalDevice m_vk_physical_device;
            vk::Device m_vk_device;
    };
}