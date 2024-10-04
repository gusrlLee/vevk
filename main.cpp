#include <iostream>
#include "vevk/vevk.h"

// TODO: 
// 지금 나는 Vulkan API 를 OpenGL을 사용하는 것 처럼 정말 간단하게 만들어 주고 싶은 Open-source 를 만드는 중이다.
// OpenGL : Init -> Shader binding -> Model loading -> Draw -> Destroy
// Vevk : Graphics Pipeline 을 따라야 하기 때문에 이 부분을 static variable로 둔다면 접근이 쉽게 될듯...? 

int main() 
{
    vevkInit();
    vevkHint(VEVK_CONTEXT_VULKAN_API_VERSION, VK_API_VERSION_1_3);
    vevkHint(VEVK_USE_VALIDATION_LAYER, VEVK_TRUE);
    vevkHint(VEVK_CONTEXT_ENV_TYPE, VEVK_MACOS);

    VEKVWindow* pWindow = vevkCreateWindow(800, 600, "Test window!");
    if (!pWindow) 
    {
        std::runtime_error("Failed to create window :-(");
        vevkTerminate();
        exit(-1);
    }   

    vevkPrintSupportedExtensionsByInstance();
    vevkPrintSupportedLayersByInstance();



    while (!vevkWindowShouldClose(pWindow))
    {
        vevkPollEvents();
    }

    vevkDestroyWindow(pWindow);
    vevkTerminate();
    return 0;
}