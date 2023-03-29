#include "AssemCube.h"

class App : public ac::Application
{
public:
	App() {}
	~App() {}
};

ac::Application* ac::CreateApplication()
{
	return new App();
}