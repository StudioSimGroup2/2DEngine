#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

namespace Engine
{
	class D3D11FrameBuffer
	{
	public:
		D3D11FrameBuffer(unsigned int width, unsigned int height);
		~D3D11FrameBuffer();

		void PrepareBuffers();

		void Load();
		void Unload();

		void OverrideColour(float r, float g, float b, float a);

		void Draw();

		void* GetTexID() { return(void*)(size_t)mTextureView; }
		
		ID3D11ShaderResourceView* GetSRV() { return mTextureView; }

	private:
		ID3D11Texture2D* mTexture = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		ID3D11ShaderResourceView* mTextureView = nullptr;
		ID3D11Buffer* mVertexBuffer = nullptr, * mIndexBuffer = nullptr;
		ID3D11Buffer* mConstantBuffer = nullptr;

		float mColour[4] = { -1, -1, -1, -1 };


		struct ConstantBuffer
		{
			DirectX::XMMATRIX mWorld;
			DirectX::XMMATRIX mView;
			DirectX::XMMATRIX mProjection;
		};

		struct VertexType
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 texture;
		};
	};

}
