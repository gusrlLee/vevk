#pragma once 

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vulkan/vulkan.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <optional>
#include <string>

#include "VkBootstrap.h"
#include "vevk_log.h"