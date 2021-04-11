#pragma once

#ifdef WINDOWS_PLATFORM

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Engine::CreateApplication();
	app->Run();

	return 0;
}
#endif

#ifdef LINUX_PLATFORM
#endif