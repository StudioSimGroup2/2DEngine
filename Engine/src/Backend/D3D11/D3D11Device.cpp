#include "D3D11Device.h"
#include <DirectXColors.h>

namespace Engine
{
	D3D11Device* D3D11Device::mInstance = nullptr;

	void D3D11Device::ClearAndSetRenderTarget()
	{
		mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView); // Set back to back buffer
		mDeviceContext->ClearRenderTargetView(mRenderTargetView, DirectX::Colors::SeaGreen);
	}

	D3D11Device* D3D11Device::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new D3D11Device();

		return mInstance;
	}

	void D3D11Device::Shutdown()
	{
		if (mInstance == nullptr)
			return;

		if (mInstance->mDevice)
			mInstance->mDevice = nullptr;

		if (mInstance->mDeviceContext)
			mInstance->mDeviceContext = nullptr;

		delete mInstance;
		mInstance = nullptr;
	}
}
