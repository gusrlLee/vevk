#pragma once 
#include "vevk_pch.h"
#include "vevk_structs.h"


/**
 * @brief Create vevk main window.
 * 
 * @param width Window width size
 * @param height Window height size 
 * @param title Window title name
 * @return * VEVKWindow* 
 */
VEVKWindow* vevkCreateWindow(uint32_t width, uint32_t height, std::string title);