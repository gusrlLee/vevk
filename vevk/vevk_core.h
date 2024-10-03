#pragma once 
#include "vevk_pch.h"
#include "vevk_gfx_context.h"

enum VEVK_HINT {
    VEVK_CONTEXT_VULKAN_API_VERSION,
    VEVK_CONTEXT_ENV_TYPE,
    VEVK_CONTEXT_INSTANCE_ADDITIONAL_EXTENSION,
    VEVK_CONTEXT_DEVICE_ADDITIONAL_EXTENSION,
    VEVK_USE_VALIDATION_LAYER
};

enum VEVK_VERSION {
    VEVK_VERSION_1_0,
};

enum VEVK_OS_TYPE {
    VEVK_WINDOW,
    VEVK_MACOS,
    VEVK_LINUX,
};

void vevkInit();

void vevkHint(VEVK_HINT hint, uint32_t value);

void vevkHint(VEVK_HINT hint, std::string extensionName);

void vevkTerminate();

VEVKGfxContext* vevkCreateGfxContext();
void vevkDestroyGfxContext(VEVKGfxContext* gfxContext);
