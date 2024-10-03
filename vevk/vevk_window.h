#pragma once 
#include "vevk_pch.h"

typedef struct VEVKWindow {
    GLFWwindow* window_handle;
    std::string title;
    uint32_t width;
    uint32_t height;
} VEKVWindow;

/**
 * @brief Create vevk main window.
 * 
 * @param width Window width size
 * @param height Window height size 
 * @param title Window title name
 * @return * VEVKWindow* VEVKWindow pointer
 */
VEVKWindow* vevkCreateWindow(uint32_t width, uint32_t height, std::string title);

/**
 * @brief Delete VEVKWindow and Destroy glfwWindow!
 * 
 * @param window Created window!
 */
void vevkDestroyWindow(VEVKWindow* window);


/**
 * @brief Checks the close flag of the specified window.
 * 
 * @param window 
 * @return true Close flag
 * @return false Open flag
 */
bool vevkWindowShouldClose(VEVKWindow* window);


/**
 * @brief Processes all pending events.
 * 
 */
void vevkPollEvents();