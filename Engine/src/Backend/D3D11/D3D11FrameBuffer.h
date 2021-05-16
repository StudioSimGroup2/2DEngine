#pragma once

#include <d3d11.h>

namespace Engine
{
	class D3D11FrameBuffer
	{
	public:
		D3D11FrameBuffer(unsigned int width, unsigned int height);
		~D3D11FrameBuffer();

		void Load();
		void Unload();

		void* GetTexID() { return(void*)(size_t)mTextureView; }

	private:
		ID3D11Texture2D* mTexture = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		ID3D11ShaderResourceView* mTextureView = nullptr;
	};

}
