#include "D3D11Texture.h"

#include <assert.h>
#include <iostream>
#include <Utils/StringHelper.h>

#include <stb/stb_image.h>

#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }

namespace Engine
{
	D3D11Texture::D3D11Texture(D3D11Device* device, const std::string& name, const std::string& path)
	{
		mName = std::string(name);
		mPath = std::string(path);
		mDeviceContext = device->GetDeviceContext();

		auto hr = S_OK;

		//mWidth = 10;
		mHeight = 64;

		hr = CreateTextureFromFile(device);
	}

	D3D11Texture::~D3D11Texture()
	{
		if (mTextureView)
		{
			mTextureView->Release();
			mTextureView = nullptr;
		}

		mDeviceContext = nullptr;
		
	}

	void D3D11Texture::Load(int pos = 0) const
	{
		mDeviceContext->VSSetShaderResources(pos, 1, &mTextureView);
		mDeviceContext->PSSetShaderResources(pos, 1, &mTextureView);
	}

	void D3D11Texture::Unload(int pos = 0) const
	{
		mDeviceContext->VSSetShaderResources(pos, 1, NULL);
		mDeviceContext->PSSetShaderResources(pos, 1, NULL);
	}

	HRESULT D3D11Texture::CreateTextureFromFile(D3D11Device* dev)
	{
		HRESULT hr = S_OK;

		int nrChannels;

		unsigned char* source = stbi_load(mPath.c_str(), &mWidth, &mHeight, &nrChannels, 0);
		if (!source) fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", source, stbi_failure_reason());

		//TODO: Error checking for nrChannels not equal to 3 or 4

		if (nrChannels == 3)
		{
			int size = mWidth * mHeight * 4;
			unsigned char* temp = new unsigned char[size];
			
			for (int i = 0; i < mWidth * mHeight; i++)
			{
				temp[i * 4] = source[i * 3];
				temp[i * 4 + 1] = source[i * 3 + 1];
				temp[i * 4 + 2] = source[i * 3 + 2];
				temp[i * 4 + 3] = 255;

				source = temp;
			}
		}

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		D3D11_SUBRESOURCE_DATA srd;
		ZeroMemory(&srd, sizeof(srd));
		ID3D11Texture2D* tex = nullptr;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));

		desc.Width = mWidth;
		desc.Height = mHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;

		//desc.Format = DXGI_FORMAT_BC1_UNORM;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		srd.pSysMem = source;
		srd.SysMemPitch = 4 * mWidth;
		srd.SysMemSlicePitch = 0;

		hr = dev->GetDevice()->CreateTexture2D(&desc, &srd, &tex);
		if (FAILED(hr))
			return hr;

		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		hr = dev->GetInstance()->GetDevice()->CreateShaderResourceView(tex, &srvDesc, &mTextureView);
		if (FAILED(hr))
			return hr;

		stbi_image_free(source);

		return hr;
	}
}