#pragma once 
#include "vevk_pch.h"

enum VEVK_HINT {
    VEVK_CONTEXT_VULKAN_API_VERSION,
    VEVK_CONTEXT_OS_TYPE,
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

typedef struct VEVKGlobalEnvironmentConfig {
    uint32_t userVulaknVersion;
    VEVK_OS_TYPE userOS;
    bool bIsUsedValidationLayer;
    std::vector<const char*> pInstanceAdditionalExtensionsNames;
    std::vector<const char*> pDeviceAdditionalExtensionsNames;
} VEVKGlobalEnvironmentConfig;

// setting for vevk
extern VEVKGlobalEnvironmentConfig gEnvConfig; 
extern class VEVKContext* gVkContext; 

/**
 * @brief 
 * 
 */
void vevkInit();

/**
 * @brief 
 * 
 * @param hint 
 * @param value 
 */
void vevkHint(VEVK_HINT hint, uint32_t value);

/**
 * @brief 
 * 
 * @param hint 
 * @param extensionName 
 */
void vevkHint(VEVK_HINT hint, std::string extensionName);


bool vevkIsSetupDone();

/**
 * @brief 
 * 
 */
void vevkTerminate();
