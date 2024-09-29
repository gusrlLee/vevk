#include "vevk_base_application.h"

namespace vevk {
	void IBaseApplication::prepare()
	{
		m_window = glfwCreateWindow(1080, 720, "Test", nullptr, nullptr);
		if (!m_window)
		{
			VEVK_ERROR("Failed to create glfw window :-(");
			glfwTerminate();
			std::exit(-1);
		}

		VEVK_INFO("Success to create glfw window! :-)");

		// TODO: we need to create vulkan api contexts 
		vkb::InstanceBuilder instance_builder;
		auto instance_ret = instance_builder
			.use_default_debug_messenger()
			.request_validation_layers()
			.build();
	
		if (!instance_ret)
		{
			VEVK_ERROR("Failed to create vulkan instance! :-(");
		}
		m_instance = instance_ret.value();
		VEVK_INFO("Sucecss to create vulkan instance! :-)");
	}


	
	void IBaseApplication::destroy()
	{
		vkb::destroy_instance(m_instance);
		glfwDestroyWindow(m_window);
	}
}