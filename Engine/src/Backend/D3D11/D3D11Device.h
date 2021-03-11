#pragma once

#include "Engine/Renderer/Device.h"

#include <d3d11.h>

#include <locale>
#include <codecvt>
#include <string>

namespace Engine
{
	class D3D11Device : public Device
	{
	public:
		D3D11Device(ID3D11Device* dev, ID3D11DeviceContext* devCon) :
			mDevice(dev), mDeviceContext(devCon) {};

		void SetDevice(ID3D11Device* dev) { mDevice = dev; }
		void SetDeviceContext(ID3D11DeviceContext* devCon) { mDeviceContext = devCon; }

		ID3D11Device* GetDevice() { return mDevice; }
		ID3D11DeviceContext* GetDeviceContext() { return mDeviceContext; }

	private:
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
	};
}
