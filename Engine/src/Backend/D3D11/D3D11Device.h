#pragma once

#include <d3d11.h>

#include <locale>
#include <codecvt>
#include <string>

namespace Engine
{
	class D3D11Device
	{
	public:
		void SetDevice(ID3D11Device* dev) { mDevice = dev; }
		void SetDeviceContext(ID3D11DeviceContext* devCon) { mDeviceContext = devCon; }

		ID3D11Device* GetDevice() { return mDevice; }
		ID3D11DeviceContext* GetDeviceContext() { return mDeviceContext; }

		static D3D11Device* GetInstance();

	private:
		D3D11Device() {}

		static D3D11Device* mInstance;

		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
	};
}
