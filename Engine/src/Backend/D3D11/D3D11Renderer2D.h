#pragma once

#include "Engine/Renderer/Renderer2D.h"
#include <Backend/D3D11/D3D11Shader.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace Engine
{
	class D3D11Renderer2D : Renderer2D
	{
	public:
		D3D11Renderer2D(D3D11Shader* shader, D3D11Device* dev);

		void Draw(vec2f position);

	private:
		void InitBuffers(ID3D11Device* dev);

		ID3D11Buffer* mVertexBuffer = nullptr, * mIndexBuffer = nullptr;
		ID3D11Buffer* mConstantBuffer;

		struct ConstantBuffer
		{
			XMMATRIX mWorld;
			XMMATRIX mView;
			XMMATRIX mProjection;
		};

		struct VertexType
		{
			XMFLOAT3 position;
			XMFLOAT2 texture;
		};

		ID3D11DeviceContext* mDeviceContext;
	};
}

