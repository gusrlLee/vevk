#include "vevk/vevk.h"

int main() {
    vevk::init();
    GLFWwindow* window = vevk::create_main_window(1280, 720, "Test");

    // *TODO - we have to implementation context 
    // auto vevk::Context gfx_context = vevk::make<vevk::Context>();




    vevk::destroy_main_window(window);
    vevk::terminate();

    return EXIT_SUCCESS;
}