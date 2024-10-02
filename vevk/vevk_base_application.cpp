#include "vevk_base_application.h"
#include "vevk_context.h"

namespace vevk {
	void IBaseApplication::prepare()
	{
		// SECTION - Make main window
		m_window = glfwCreateWindow(1080, 720, "Test", nullptr, nullptr);
		if (!m_window)
		{
			VEVK_ERROR("Failed to create glfw window :-(");
			glfwTerminate();
			std::exit(-1);
		}

		VEVK_INFO("Success to create glfw window! :-)");

		// SECTION - Make vulkan context
		m_ctx = make<vevk::Context>();
		m_ctx->prepare(m_window);
	}
	
	void IBaseApplication::destroy()
	{
		m_ctx->destroy();
		glfwDestroyWindow(m_window);
	}

	void IBaseApplication::run() {
		while (!glfwWindowShouldClose(m_window)) {
			glfwPollEvents();
		}
	}
}