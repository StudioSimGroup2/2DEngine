#include "D3D11Texture.h"

#include "DDSTextureLoader.h"

#include <assert.h>
#include <iostream>
#include <Utils/StringToWString.h>

#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }

namespace Engine
{
	D3D11Texture::D3D11Texture(D3D11Device* device, const std::string& path, const std::string name, int ID)
	{
		mName = name;
		mID = ID;
		mDeviceContext = device->GetDeviceContext();

		auto hr = S_OK;

		mWidth = 32;
		mHeight = 32;

		hr = DirectX::CreateDDSTextureFromFile(device->GetDevice(), utf8ToUtf16(path).c_str(), nullptr, &mTexture);
	}

	D3D11Texture::~D3D11Texture()
	{
	}

	void D3D11Texture::Load(int pos) const
	{
		mDeviceContext->VSSetShaderResources(0, pos, &mTexture);
		mDeviceContext->PSSetShaderResources(0, pos, &mTexture);
	}

	void D3D11Texture::Unload(int pos) const
	{
		mDeviceContext->VSSetShaderResources(0, pos, NULL);
		mDeviceContext->PSSetShaderResources(0, pos, NULL);
	}
}