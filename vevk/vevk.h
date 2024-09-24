#pragma once 
#include "vevk_types.h"
#include "vevk_window.h"
#include "vevk_context.h"

namespace vevk {
    extern bool is_enable_validation_layer;

    enum Features {
        VEVK_VALIDATION_LAYER,
    };

    enum Options {
        VEVK_NO_USE_VALIDATION_LAYER,
        VEVK_USE_VALIDATION_LAYER
    };

    void init();
    void hint(Features feature, Options opt);
    void terminate();
}