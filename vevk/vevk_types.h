#pragma once 

#include <iostream>
#include <optional>
#include <map>
#include <memory>

namespace vevk {
    
template<typename T>
using ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr ref<T> make(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}
