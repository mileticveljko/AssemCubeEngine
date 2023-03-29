#pragma once

#include "Core.h"

namespace ac {

	class AC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in a cliant
	Application* CreateApplication();
}