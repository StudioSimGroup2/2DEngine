#include "D3D11Device.h"

namespace Engine
{
	D3D11Device* D3D11Device::mInstance = nullptr;

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
