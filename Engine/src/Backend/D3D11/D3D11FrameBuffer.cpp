#include "D3D11FrameBuffer.h"
#include "Backend\D3D11\D3D11Device.h"
#include <DirectXColors.h>
#include "CameraManager.h"

namespace Engine
{
	D3D11FrameBuffer::D3D11FrameBuffer(unsigned int width, unsigned int height)
	{
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		D3D11Device::GetInstance()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &mTexture);

		// Setup the description of the render target view.
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
		D3D11Device::GetInstance()->GetDevice()->CreateRenderTargetView(mTexture, &renderTargetViewDesc, &mRenderTargetView);

		// Setup the description of the shader resource view.
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		D3D11Device::GetInstance()->GetDevice()->CreateShaderResourceView(mTexture, &shaderResourceViewDesc, &mTextureView);
	}

	D3D11FrameBuffer::~D3D11FrameBuffer()
	{
		if (mTextureView)
		{
			Unload();

			mTextureView->Release();
			mTextureView = nullptr;
		}

		if (mRenderTargetView)
		{
			mRenderTargetView->Release();
			mRenderTargetView = nullptr;
		}

		if (mTexture)
		{
			mTexture->Release();
			mTexture = nullptr;
		}
	}

	void D3D11FrameBuffer::PrepareBuffers()
	{
		auto hr = S_OK;
		VertexType vertices[6];
		float left, right, top, bottom;

		// Calculate the screen coordinates of the left side of the bitmap.
		left = 0; // 0 = X position

		// Calculate the screen coordinates of the right side of the bitmap.
		right = left + (float)1260;

		// Calculate the screen coordinates of the top of the bitmap.
		top = 0; // 0 = Y position

		// Calculate the screen coordinates of the bottom of the bitmap.
		bottom = top - (float)677;

		// Bad triangle
		vertices[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		vertices[0].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

		vertices[1].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
		vertices[1].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

		vertices[2].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom left.
		vertices[2].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

		// Second triangle. Good triangle
		vertices[3].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		vertices[3].texture = DirectX::XMFLOAT2(0.0f, 0.0f);

		vertices[4].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		vertices[4].texture = DirectX::XMFLOAT2(1.0f, 0.0f);

		vertices[5].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
		vertices[5].texture = DirectX::XMFLOAT2(1.0f, 1.0f);


		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VertexType) * 6;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		D3D11Device::GetInstance()->GetDevice()->CreateBuffer(&bd, &InitData, &mVertexBuffer);

		// I dont think these are working corretly
		WORD indices[] = {
			0, 1, 2,
			3, 4, 5,
		};

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		D3D11Device::GetInstance()->GetDevice()->CreateBuffer(&bd, &InitData, &mIndexBuffer);

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11Device::GetInstance()->GetDevice()->CreateBuffer(&bd, nullptr, &mConstantBuffer);


		D3D11Device::GetInstance()->GetDevice()->CreateBuffer(&bd, nullptr, &mConstantBuffer);
	}

	void D3D11FrameBuffer::Load()
	{
		D3D11Device::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, &mRenderTargetView, D3D11Device::GetInstance()->GetDepthStencilView());

		(mColour[3] == -1) ? D3D11Device::GetInstance()->GetDeviceContext()->ClearRenderTargetView(mRenderTargetView, DirectX::Colors::SeaGreen) :
			D3D11Device::GetInstance()->GetDeviceContext()->ClearRenderTargetView(mRenderTargetView, mColour);
		
	}

	void D3D11FrameBuffer::Unload()
	{	
		D3D11Device::GetInstance()->GetDeviceContext()->ClearDepthStencilView(D3D11Device::GetInstance()->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
		D3D11Device::GetInstance()->ClearAndSetRenderTarget();
	}

	void D3D11FrameBuffer::OverrideColour(float r, float g, float b, float a)
	{
		mColour[0] = r;
		mColour[1] = g;
		mColour[2] = b;
		mColour[3] = a;
	}

	void D3D11FrameBuffer::Draw()
	{
		auto camera = CameraManager::Get()->GetPrimaryCamera();

		ConstantBuffer cb;
		cb.mProjection = DirectX::XMMatrixTranspose(camera->GetProjectionMatrix());
		cb.mView = DirectX::XMMatrixTranspose(camera->GetViewMatrix());
		cb.mWorld = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());

		D3D11Device::GetInstance()->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, nullptr, &cb, 0, 0);
		D3D11Device::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
		D3D11Device::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(0, 1, &mConstantBuffer);

		UINT stride = sizeof(VertexType);
		UINT offset = 0;

		D3D11Device::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		D3D11Device::GetInstance()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		D3D11Device::GetInstance()->GetDeviceContext()->Draw(6, 0);
	}
}