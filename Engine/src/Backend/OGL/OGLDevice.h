#pragma once

#include <windows.h>
#include <string>
#include <utility>

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC, HGLRC, const int*);

struct DeviceData
{
	std::string mGraphicsCardName;
	int mGraphicsCardTotalMemory;
	std::string mRendererAPI;

	DeviceData(std::string cardName, int totalMem)
	{
		mGraphicsCardName = std::move(cardName);
		mGraphicsCardTotalMemory = totalMem;

		mRendererAPI = std::string("OpenGL 4.6");
	}

	DeviceData()
	{
		mGraphicsCardName = "";
		mGraphicsCardTotalMemory = 0;

		mRendererAPI = "";
	}
};

namespace Engine
{
	class OGLDevice
	{
	public:
		void SetHGLRC(HGLRC hglrc) { mHGLRC = hglrc; }

		void SetDeviceData(const DeviceData& devData) { mDeviceData = devData; }

		HGLRC GetHGLRC() { return mHGLRC; }

		DeviceData GetDeviceData() { return mDeviceData; }

		static OGLDevice* GetInstance();

	private:
		OGLDevice() = default;

		static OGLDevice* mInstance;

		HGLRC mHGLRC;

		DeviceData mDeviceData;
	};
}

