#pragma once 

#include <iostream>
#include <optional>
#include <map>
#include <memory>

namespace vevk {
    
template<typename T>
using Ptr = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ptr<T> make(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}


template<typename T>
using ResultCheck = std::optional<T>;

}
