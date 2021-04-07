#pragma once

#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);

namespace Engine
{
	class OGLDevice
	{
	public:
		void SetHGLRC(HGLRC hglrc) { mHGLRC = hglrc; }

		HGLRC GetHGLRC() { return mHGLRC; }

		static OGLDevice* GetInstance();

	private:
		OGLDevice() {}

		static OGLDevice* mInstance;

		HGLRC mHGLRC;
	};
}

