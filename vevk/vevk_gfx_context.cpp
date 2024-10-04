#include "vevk_gfx_context.h"

void VEVKGfxContext::prepare(VEVKGfxContextCreateInfo createInfo) 
{
    VkApplicationInfo appInfo{};
    appInfo.pApplicationName = "VEVK Test app";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "VEVK Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = createInfo.userVulaknVersion;

    

    VkInstanceCreateInfo instanceInfo{};
}

void VEVKGfxContext::destroy() 
{

}