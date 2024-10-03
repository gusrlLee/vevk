#include "vevk_window.h"

VEVKWindow* vevkCreateWindow(uint32_t width, uint32_t height, std::string title) 
{
    VEVKWindow* window = new VEVKWindow();
    window->width = width;
    window->height = height;
    window->title = title;
    window->window_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window->window_handle) 
    {
        return nullptr;
    }

    return window;
}

void vevkDestroyWindow(VEVKWindow* window) 
{
    glfwDestroyWindow(window->window_handle);
    delete window;
}

bool vevkWindowShouldClose(VEVKWindow* window) 
{
    return glfwWindowShouldClose(window->window_handle);
}

void vevkPollEvents() 
{
    glfwPollEvents();
}