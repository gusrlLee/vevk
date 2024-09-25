#pragma once 

#include <iostream>
#include <optional>
#include <map>
#include <memory>

namespace vevk {
    
template<typename T>
using ptr = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr ptr<T> make(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}


template<typename T>
using ResultCheck = std::optional<T>;

}
