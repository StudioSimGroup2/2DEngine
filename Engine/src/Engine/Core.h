#pragma once

#ifdef WINDOWS_PLATFORM
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // BUILD_DLL
#else
#error Unsupported platform.
#endif