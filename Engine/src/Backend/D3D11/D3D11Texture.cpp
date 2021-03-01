#include "D3D11Texture.h"

#include "DDSTextureLoader.h"

#include <assert.h>
#include <iostream>
#include <Utils/StringHelper.h>

#include <stb/stb_image.h>

#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }

namespace Engine
{
	D3D11Texture::D3D11Texture(D3D11Device* device, const std::string& name, const std::string& path)
	{
		mName = name;
		mDeviceContext = device->GetDeviceContext();

		auto hr = S_OK;

		mWidth = 32;
		mHeight = 32;

		hr = DirectX::CreateDDSTextureFromFile(device->GetDevice(), StringHelper::StringToWide(path).c_str(), nullptr, &mTextureView);
	}

	D3D11Texture::~D3D11Texture()
	{
	}

	void D3D11Texture::Load(int pos = 1) const
	{
		mDeviceContext->VSSetShaderResources(0, pos, &mTextureView);
		mDeviceContext->PSSetShaderResources(0, pos, &mTextureView);
	}

	void D3D11Texture::Unload(int pos = 1) const
	{
		mDeviceContext->VSSetShaderResources(0, pos, NULL);
		mDeviceContext->PSSetShaderResources(0, pos, NULL);
	}
}