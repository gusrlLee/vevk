#include "vevk/vevk.h"
#include "vevk/vevk_instance.h"
#include "vevk/vevk_debug_messenger.h"
#include "vevk/vevk_device.h"

int main() {
    vevk::init();
    GLFWwindow* window = vevk::create_main_window(1280, 720, "Test");

    // *TODO - we have to implementation context 
    // auto vevk::Context gfx_context = vevk::make<vevk::Context>();

    // NOTE - Instance 
    vk::Instance instance = vevk::create_instance("Vevk!", true);
    // NOTE - Dispatch loader dynamic 
    vk::DispatchLoaderDynamic dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);
    // NOTE - Debug messenger 
    vk::DebugUtilsMessengerEXT messenger = vevk::make_debug_messenger(instance, dldi);
    // NOTE - Physical device 
    vk::PhysicalDevice choosed_device = vevk::choose_physical_device(instance);

    // Deallocation
    instance.destroyDebugUtilsMessengerEXT(messenger, nullptr, dldi);
    instance.destroy();

    vevk::destroy_main_window(window);
    vevk::terminate();

    return EXIT_SUCCESS;
}