#pragma once 
#include "vevk_pch.h"

// SECTION - Extensions & Layer check or getting functions
/**
 * @brief 
 * 
 * @param extensionNameList 
 * @param extensionCount 
 * @return true 
 * @return false 
 */
bool vevkCheckSupportedExtensionsByInstance(const char** extensionNameList, int extensionCount);

/**
 * @brief 
 * 
 */
void vevkPrintSupportedExtensionsByInstance();

/**
 * @brief 
 * 
 * @param layerNameList 
 * @param layerCount 
 * @return true 
 * @return false 
 */
bool vevkCheckSupportedLayersByInstance(const char** layerNameList, int layerCount);

/**
 * @brief 
 * 
 */
void vevkPrintSupportedLayersByInstance();

/**
 * @brief 
 * 
 * @return std::vector<const char*> 
 */
std::vector<const char*> vevkGetRequiredExtensions();

/**
 * @brief 
 * 
 * @return std::vector<const char*> 
 */
std::vector<const char*> vevkGetRequiredLayers();


// SECTION - Make basic create info functions 

/**
 * @brief 
 * 
 * @return VkApplicationInfo 
 */
VkApplicationInfo vevkMakeApplicationInfo();


/**
 * @brief 
 * 
 * @return VkInstanceCreateInfo 
 */
VkInstanceCreateInfo vevkMakeInstanceInfo();


VkDebugUtilsMessengerCreateInfoEXT vevkMakeDebugMessengerCreateInfo();

VkResult vevkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void vevkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);