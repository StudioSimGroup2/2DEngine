#pragma once

#include "Utils/Texture.h"
#include <Backend/D3D11/D3D11Device.h>

#include <string>
#include <d3d11.h>
#include <DirectXColors.h>

#define STB_IMAGE_IMPLEMENTATION

using namespace DirectX;

namespace Engine
{
	class D3D11Texture : public Texture
	{
	public:
		D3D11Texture(D3D11Device* device, const std::string& name, const std::string& path);
		~D3D11Texture();

		virtual void Load(int pos) const override;
		virtual void Unload(int pos) const override;

		void* GetTexID() override { return (void*)(size_t)mTextureView; }

		HRESULT CreateTextureFromFile(D3D11Device* dev);

	private:

		ID3D11ShaderResourceView* mTextureView = nullptr;

		ID3D11DeviceContext* mDeviceContext; // is this being used? - yes it is i'm blind
	};
}