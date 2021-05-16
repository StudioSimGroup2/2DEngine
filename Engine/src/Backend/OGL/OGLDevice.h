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
		void SetHDC(HDC hDC) { mHDC = hDC; }
		void SetHGLRC(HGLRC hglrc) { mHGLRC = hglrc; }
		void SetHWND(HWND hWnd) { mHWND = hWnd; }

		void SetDeviceData(const DeviceData& devData) { mDeviceData = devData; }

		HGLRC GetHGLRC() { return mHGLRC; }
		HDC GetHDC() { return mHDC; }
		HWND GetHWND() { return mHWND; }

		DeviceData GetDeviceData() { return mDeviceData; }

		static OGLDevice* GetInstance();

		void ShutdownDevice();

	private:
		OGLDevice() = default;

		static OGLDevice* mInstance;

		HGLRC mHGLRC;
		HDC mHDC;
		HWND mHWND;

		DeviceData mDeviceData;
	};
}

