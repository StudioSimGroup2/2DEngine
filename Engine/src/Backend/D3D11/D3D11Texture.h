#pragma once

#include "Utils/Texture.h"
#include <Backend/D3D11/D3D11Device.h>

#include <string>
#include <d3d11.h>
#include <DirectXColors.h>

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

		virtual const std::string& GetName() const override { return mName; }

	private:
		unsigned int mID, mBoundSlot = -1;
		unsigned int mWidth, mHeight;

		ID3D11ShaderResourceView* mTexture = nullptr;

		ID3D11DeviceContext* mDeviceContext;
	};
}