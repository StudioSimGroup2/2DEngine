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
}
