#include "D3D11Renderer2D.h"

#include "D3D11Device.h"
#include <CameraManager.h>

namespace Engine
{
	D3D11Renderer2D::D3D11Renderer2D(D3D11Shader* shader, D3D11Device* dev)
	{
		mShader = static_cast<Shader*>(shader);

		mDeviceContext = dev->GetDeviceContext();

		InitBuffers(dev->GetDevice());
	}

	void D3D11Renderer2D::Draw(vec2f position, Texture* textureToRender) const
	{
		Camera* camera = CameraManager::Get()->GetPrimaryCamera();

		XMMATRIX mScale = XMMatrixScaling(1, 1.05f, 1);
		XMMATRIX mRotate = XMMatrixRotationX(0) * XMMatrixRotationY(0) * XMMatrixRotationZ(0);
		XMMATRIX mTranslate = XMMatrixTranslation(position.x, -position.y, 0);
		XMMATRIX world = mScale * mRotate * mTranslate;

		ConstantBuffer cb;
		cb.mProjection = XMMatrixTranspose(camera->GetProjectionMatrix());
		cb.mView = XMMatrixTranspose(camera->GetViewMatrix());
		cb.mWorld = XMMatrixTranspose(world);

		mDeviceContext->UpdateSubresource(mConstantBuffer, 0, nullptr, &cb, 0, 0);
		mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
		mDeviceContext->PSSetConstantBuffers(0, 1, &mConstantBuffer);

		UINT stride = sizeof(VertexType);
		UINT offset = 0;

		mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		mShader->Load();

		textureToRender->Load();

		mDeviceContext->Draw(6, 0);
	}

	void D3D11Renderer2D::InitBuffers(ID3D11Device* dev)
	{
		auto hr = S_OK;
		VertexType vertices[6];
		float left, right, top, bottom;

		// Calculate the screen coordinates of the left side of the bitmap.
		left = (float)((1280 / 2) * -1); // 0 = X position

		// Calculate the screen coordinates of the right side of the bitmap.
		right = left + (float)32;

		// Calculate the screen coordinates of the top of the bitmap.
		top = (float)(720 / 2); // 0 = Y position

		// Calculate the screen coordinates of the bottom of the bitmap.
		bottom = top - (float)32;

		// Bad triangle
		vertices[0].position = XMFLOAT3(left, top, 0.0f);  // Top left.
		vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

		vertices[1].position = XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		vertices[1].texture = XMFLOAT2(0.0f, 1.0f);

		vertices[2].position = XMFLOAT3(right, bottom, 0.0f);  // Bottom left.
		vertices[2].texture = XMFLOAT2(1.0f, 1.0f);

		// Second triangle. Good triangle
		vertices[3].position = XMFLOAT3(left, top, 0.0f);  // Top left.
		vertices[3].texture = XMFLOAT2(0.0f, 0.0f);

		vertices[4].position = XMFLOAT3(right, top, 0.0f);  // Top right.
		vertices[4].texture = XMFLOAT2(1.0f, 0.0f);

		vertices[5].position = XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		vertices[5].texture = XMFLOAT2(1.0f, 1.0f);

		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VertexType) * 6;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		hr = dev->CreateBuffer(&bd, &InitData, &mVertexBuffer);
		ASSERT(!FAILED(hr), "Error creating vertex buffer");

		// I dont think these are working corretly
		WORD indices[] = {
			2, 1, 0,
			5, 4, 3,
		};

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		hr = dev->CreateBuffer(&bd, &InitData, &mIndexBuffer);
		ASSERT(!FAILED(hr), "Error creating Index buffer");

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		hr = dev->CreateBuffer(&bd, nullptr, &mConstantBuffer);
		ASSERT(!FAILED(hr), "Error creating Constant buffer");
	}
}