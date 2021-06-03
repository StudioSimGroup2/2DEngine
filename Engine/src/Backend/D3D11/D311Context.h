#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

#include "Engine/Renderer/Context.h"

//Can be removed added for testing
//#include "ParticalSystem.h"
//----------------------------------

using namespace DirectX;

namespace Engine
{
	class D311Context : public Context
	{
	public:
		D311Context(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen);
		~D311Context();
		
		void Init() override;
		void Shutdown() override;
		void OnUpdate(float deltaTime) override;

		virtual void SwapBuffers() override;

		void RenderImGui();
		void RenderScene();
		
	private:

		UINT32 mScreenWidth;
		UINT32 mScreenHeight;

		HWND mHWND;

		IDXGISwapChain* mSwapChain = nullptr;
		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mDeviceContext = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		ID3D11Texture2D* mDepthStencilBuffer = nullptr;
		ID3D11DepthStencilState* mDepthStencilState = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;
		ID3D11BlendState* mTransparant = nullptr;
		ID3D11RasterizerState* mRasterState = nullptr;

#ifdef _DEBUG
		ID3D11Debug* mDebug = nullptr;
		ID3D11InfoQueue* mInfoQueue = nullptr;
#endif

		XMMATRIX mWorldMatrix;
		XMMATRIX mOrthoMatrix;

		//These should be in the GameScreenTest
		//std::vector<ParticleSystem*> mParticleSystems;


	};
}