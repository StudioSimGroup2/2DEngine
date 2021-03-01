#include "WindowsTextureCompiler.h"

#include "Utils/StringHelper.h"

namespace Engine
{
	BYTE* WindowsTextureCompiler::LoadImageFromFile(const std::string& path)
	{
		auto hr = S_OK;

		hr = CoInitialize(NULL);

		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&wicImagingFactory);

		IWICBitmapDecoder* decoder;
		IWICBitmapFrameDecode* source = NULL;
		IWICStream* stream = NULL;
		IWICFormatConverter* converter = NULL;
		IWICBitmapScaler* scaler = NULL;
		IWICBitmap* bitmap = NULL;

		hr = wicImagingFactory->CreateDecoderFromFilename(StringHelper::StringToWide(path).c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

		if (SUCCEEDED(hr))
		{
			hr = decoder->GetFrame(0, &source);
		}

		if (SUCCEEDED(hr))
		{
			hr = wicImagingFactory->CreateFormatConverter(&converter);
		}

		WICPixelFormatGUID pixelFormat;

		if (SUCCEEDED(hr))
		{
			hr = source->GetPixelFormat(&pixelFormat);
		}

		BOOL result = false;

		if (SUCCEEDED(hr))
		{
			hr = converter->CanConvert(pixelFormat, GUID_WICPixelFormat32bppRGBA, &result);
		}

		if (SUCCEEDED(hr) && (result == true))
		{
			hr = converter->Initialize(source, GUID_WICPixelFormat32bppRGBA,
				WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
		}

		if (SUCCEEDED(hr))
		{
			hr = wicImagingFactory->CreateBitmapFromSource(converter, WICBitmapCacheOnDemand, &bitmap);
		}

		UINT imgWidth = 0, imgHeight = 0;

		if (SUCCEEDED(hr))
		{
			hr = bitmap->GetSize(&imgWidth, &imgHeight);
		}

		WICRect rect = { 0, 0, imgWidth, imgHeight };

		IWICBitmapLock* lock = nullptr;

		if (SUCCEEDED(hr))
		{
			hr = bitmap->Lock(&rect, WICBitmapLockRead, &lock);
		}

		UINT bufferSze = 0;
		BYTE* buffer = nullptr;

		if (SUCCEEDED(hr))
		{
			hr = lock->GetDataPointer(&bufferSze, &buffer);
		}

		if (SUCCEEDED(hr))
		{
			return buffer;
		}

		return nullptr;
	}

	WindowsTextureCompiler::~WindowsTextureCompiler()
	{
		
	}
}


