#include <iostream>
#include "vevk/vevk.h"

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

    VEVKGfxContext* gfxContext = vevkCreateGfxContext();

    while (!vevkWindowShouldClose(pWindow))
    {
        vevkPollEvents();
    }


    vevkDestroyGfxContext(gfxContext);
    vevkDestroyWindow(pWindow);
    vevkTerminate();
    return 0;
}