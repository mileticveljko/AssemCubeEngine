#pragma once

#include "Core.h"

#include "Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Core/Events/ApplicationEvent.h"

#include "Core/ImGui/ImGuiLayer.h"

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/VertexArray.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	// To be defined in a cliant
	Application* CreateApplication();
}