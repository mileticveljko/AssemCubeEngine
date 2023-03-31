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
		if (ac::Input::IsKeyPressed(AC_KEY_TAB))
			AC_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(ac::Event& event) override
	{
		if (event.GetEventType() == ac::EventType::KeyPressed)
		{
			ac::KeyPressedEvent& e = (ac::KeyPressedEvent&)event;
			if (e.GetKeyCode() == AC_KEY_TAB)
				AC_TRACE("Tab key is pressed (event)!");
			AC_TRACE("{0}", (char)e.GetKeyCode());
		}
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