#pragma once 
#include "vevk_pch.h"

typedef struct VEVKGfxContextCreateInfo {
    uint32_t userVulaknVersion;
    bool bIsUsedValidationLayer;
    std::vector<const char*> pInstanceAdditionalExtensionsNames;
    std::vector<const char*> pDeviceAdditionalExtensionsNames;

} VEVKGfxContextCreateInfo;

class VEVKGfxContext {
    public:
        void prepare(VEVKGfxContextCreateInfo createInfo);
        void destroy();

    private:
        VkInstance mInstance;
};