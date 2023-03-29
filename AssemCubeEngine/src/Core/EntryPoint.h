#pragma once

#ifdef AC_PLATFORM_WINDOWS

extern ac::Application* ac::CreateApplication();

int main(int argc, char** argv)
{
	auto app = ac::CreateApplication();
	app->Run();
	delete app;
}
#endif
