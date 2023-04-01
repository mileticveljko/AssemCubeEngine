#pragma once

#include "Core.h"

#include "Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Core/Events/ApplicationEvent.h"

#include "Core/ImGui/ImGuiLayer.h"

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"

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

		unsigned int m_VertexArray;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in a cliant
	Application* CreateApplication();
}