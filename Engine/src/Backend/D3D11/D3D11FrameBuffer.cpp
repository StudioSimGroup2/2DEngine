#include "D3D11FrameBuffer.h"
#include "Backend\D3D11\D3D11Device.h"
#include <DirectXColors.h>

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

	void D3D11FrameBuffer::Load()
	{
		D3D11Device::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, &mRenderTargetView, D3D11Device::GetInstance()->GetDepthStencilView());
		D3D11Device::GetInstance()->GetDeviceContext()->ClearRenderTargetView(mRenderTargetView, DirectX::Colors::SeaGreen);
		
	}

	void D3D11FrameBuffer::Unload()
	{	
		D3D11Device::GetInstance()->GetDeviceContext()->ClearDepthStencilView(D3D11Device::GetInstance()->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
		D3D11Device::GetInstance()->ClearAndSetRenderTarget();
	}
}