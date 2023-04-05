#pragma once

#include "Core.h"

#include "Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Core/Events/ApplicationEvent.h"

#include "Core/ImGui/ImGuiLayer.h"

#include "Core/Timestep.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in a cliant
	Application* CreateApplication();
}