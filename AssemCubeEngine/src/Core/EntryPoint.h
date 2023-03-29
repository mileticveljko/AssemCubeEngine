#pragma once

#ifdef AC_PLATFORM_WINDOWS

extern ac::Application* ac::CreateApplication();

int main(int argc, char** argv)
{
	ac::Log::Init();
	AC_CORE_INFO("M");
	int a = 5;
	AC_ERROR("V {0}",a);

	auto app = ac::CreateApplication();
	app->Run();
	delete app;
}
#endif
