#include "AssemCube.h"

class ExampleLayer : public ac::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		AC_INFO("ExampleLayer::Update");
	}

	void OnEvent(ac::Event& event) override
	{
		AC_TRACE("{0}", event);
	}
};

class App : public ac::Application
{
public:
	App() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ac::ImGuiLayer());
	}
	~App() {}
};

ac::Application* ac::CreateApplication()
{
	return new App();
}