#pragma once

#include "Engine/Renderer/Renderer2D.h"

#include <DirectXMath.h>
#include <GLM/matrix.hpp>

#include <Backend/D3D11/D3D11Shader.h>
#include <Backend/D3D11/D3D11Texture.h>

using namespace DirectX;

namespace Engine
{
	class D3D11Renderer2D : public Renderer2D
	{
	public:
		D3D11Renderer2D(Shader* shader, D3D11Device* dev);
		D3D11Renderer2D(Shader* shader, D3D11Device* dev, int cellWidth, int cellHeight, vec2i position);
		~D3D11Renderer2D();

		void Draw(vec2f& position, vec2f& rotation, vec2f& scale, Texture* textureToRender) override;

		virtual void UpdateBuffers(int cellWidth, int cellHeight, int posX, int posY) override;
		 
	private:
		void InitBuffers(ID3D11Device* dev, int cellWidth = -1, int cellHeight = -1, int posX = -1, int posY = -1);

		ID3D11Buffer* mVertexBuffer = nullptr, * mIndexBuffer = nullptr;
		ID3D11Buffer* mConstantBuffer;
		ID3D11Buffer* mColourBuffer;

		//DirectX::XMMATRIX mWorld;

		struct ConstantBuffer
		{
			XMMATRIX mWorld;
			XMMATRIX mView;
			XMMATRIX mProjection;
			int mFlipX;
			int mFlipY;
			XMFLOAT2 padding;
		};

		struct ColourBuffer
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct VertexType
		{
			XMFLOAT3 position;
			XMFLOAT2 texture;
		};

		ID3D11DeviceContext* mDeviceContext;
	};
}

