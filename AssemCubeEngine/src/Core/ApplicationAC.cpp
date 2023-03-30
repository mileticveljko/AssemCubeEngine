#include "acpch.h"

#include "ApplicationAC.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Log.h"

namespace ac {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			AC_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			AC_TRACE(e);
		}
		while (true);
	}

}