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
	}
	
	void IBaseApplication::destroy()
	{
		glfwDestroyWindow(m_window);
	}
}