#pragma once

///
/// Code based off https://docs.microsoft.com/en-gb/windows/win32/direct2d/how-to-load-a-direct2d-bitmap-from-a-file
/// 

#include <wincodec.h>
#include <wincodecsdk.h>
#pragma comment(lib, "WindowsCodecs.lib")
#include <atlbase.h>
#include <string>

namespace Engine
{
	class WindowsTextureCompiler
	{
	public:
		BYTE* LoadImageFromFile(const std::string& path);
		~WindowsTextureCompiler();

	private:
		IWICImagingFactory* wicImagingFactory = nullptr;
	};
}



