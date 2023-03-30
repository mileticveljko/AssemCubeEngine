#include "acpch.h"

#include "ApplicationAC.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Log.h"

#include <GLFW/glfw3.h>

namespace ac {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.7, 0.8, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}