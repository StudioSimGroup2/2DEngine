#pragma once

#include "Engine/Renderer/Context.h"
#include "Sprite.h"
#include "GameScreenManager.h"

// TODO: add compiler include path later or Precompiled Header

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "D3D11/imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
#include <vector>

//Can be removed added for testing
#include "LevelMap.h"
#include "Common.h"
#include "Character.h"
#include "ParticalSystem.h"
#include <Backend/D3D11/D3D11Device.h>
#include <time.h>

#include "Utils\logger.h"
//----------------------------------

using namespace DirectX;

namespace Engine
{
	class D311Context : public Context
	{
	public:
		D311Context(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen);
		~D311Context();
		
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void SwapBuffers() override;

		virtual int GetCardMemory() override { return mMemorySize; }
		virtual std::string GetCardName() override  { return mName; }

		void RenderImGui();
		void RenderScene();
		
	private:
		unsigned int mMemorySize;
		std::string mName;

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

		XMMATRIX mWorldMatrix;
		XMMATRIX mOrthoMatrix;


		//TODO change name 
		GameScreenManager* mGameScreenManager;

		//These should be in the GameScreenTest
		//Move IMGUI to GameScreenTest too so it doesn't render on playable screens & less work needs to be done to fix OGLContext
		std::vector<ParticleSystem*> mParticleSystems;
		std::vector<Character*> mCharacters;
	


		AssetManager* mAssetManager;
		D3D11Device* mDeviceMGR;

		bool mEnableEditor = true; // Very curde, will set up an ImGUi properties struct later - Joe
		bool mShowLoggingConsole = true;

		// Render to texture for imgui
		ID3D11Texture2D* mRTTRrenderTargetTexture = nullptr;			// Texture to render to 
		ID3D11RenderTargetView* mRTTRenderTargetView = nullptr;		// Render target
		ID3D11ShaderResourceView* mRTTShaderResourceView = nullptr;	// Shader resource view for the texture
	};
}