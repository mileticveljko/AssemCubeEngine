#pragma once

#include "Core.h"

#include "Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Core/Events/ApplicationEvent.h"


namespace ac {

	class AC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		void Run();

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in a cliant
	Application* CreateApplication();
}