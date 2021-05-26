#pragma once

#include <d3d11.h>

#include <locale>
#include <codecvt>
#include <string>
#include <utility>

struct DeviceData
{
	std::string mGraphicsCardName;
	int mGraphicsCardTotalMemory;
	std::string mRendererAPI;

	DeviceData(std::string cardName, int totalMem)
	{
		mGraphicsCardName = std::move(cardName);
		mGraphicsCardTotalMemory = totalMem;

		mRendererAPI = std::string("DirectX 11");
	}
	
	DeviceData()
	{
		mGraphicsCardName = "";
		mGraphicsCardTotalMemory = 0;

		mRendererAPI = "";
	}
};

namespace Engine
{
	class D3D11Device
	{
	public:
		void SetDevice(ID3D11Device* dev) { mDevice = dev; }
		void SetDeviceContext(ID3D11DeviceContext* devCon) { mDeviceContext = devCon; }
		void SetDeviceData(const DeviceData& devData) { mDeviceData = devData; }
		void SetDepthStencilView(ID3D11DepthStencilView* dSV) { mDepthStencilView = dSV; };
		void SetRenderTargetView(ID3D11RenderTargetView* rTV) { mRenderTargetView = rTV; }

		ID3D11Device* GetDevice() { return mDevice; }
		ID3D11DeviceContext* GetDeviceContext() { return mDeviceContext; }
		ID3D11DepthStencilView* GetDepthStencilView() { return mDepthStencilView; }
		ID3D11RenderTargetView* GetRenderTargetView() { return mRenderTargetView; }

		void ClearAndSetRenderTarget();

		DeviceData GetDeviceData() { return mDeviceData; }

		static D3D11Device* GetInstance();

		static void Shutdown();

	private:
		D3D11Device() = default;

		static D3D11Device* mInstance;

		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mDeviceContext = nullptr;

		DeviceData mDeviceData;

		ID3D11DepthStencilView* mDepthStencilView = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
	};
}
