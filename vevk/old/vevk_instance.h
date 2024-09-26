#pragma once 

#include "vevk_pch.h"
#include "vevk_types.h"

namespace vevk {

bool check_supported_extensions_by_instance(const char** extention_name_list, int extension_count);

bool check_supported_layers_by_instance(const char** layer_name_list, int layer_count);

std::vector<const char*> get_required_extensions();

vk::Instance create_instance(std::string application_name);

}