#pragma once 
#include "vevk_pch.h"


#define VEVK_TRUE true
#define VEVK_FALSE false
#define VEVK_SUCCESS true
#define VEVK_FALSE false

template<typename T>
using ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr ref<T> make(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}