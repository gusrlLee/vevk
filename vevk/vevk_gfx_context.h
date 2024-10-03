#pragma once 
#include "vevk_pch.h"

typedef struct VEVKGfxContextCreateInfo {
    uint32_t userVulaknVersion;
    bool bIsUsedValidationLayer;
    std::vector<const char*> pInstanceExtensionsNames;
    std::vector<const char*> pDeviceExtensionsNames;

} VEVKGfxContextCreateInfo;

class VEVKGfxContext {

};