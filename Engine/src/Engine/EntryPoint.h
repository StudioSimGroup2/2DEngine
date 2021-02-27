#pragma once

#ifdef WINDOWS_PLATFORM

#define USE_OPENGL

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Engine::CreateApplication();
	app->Run();
}
#endif

#ifdef LINUX_PLATFORM
#endif