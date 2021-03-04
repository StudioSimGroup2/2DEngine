#pragma once

#include "../../Engine/Renderer/Context.h"
#include "../../../Sprite.h"

// TODO: add compiler include path later or Precompiled Header
#include "../../../vendor/ImGui/imgui.h"
#include "../../../vendor/ImGui/imgui_impl_win32.h"
#include "../../../vendor/ImGui/imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
#include <vector>

//Can be removed added for testing
#include "../../../LevelMap.h"
#include "../../../Common.h"
#include "../../../Character.h"
#include "../../../TinyXML/tinyxml.h"
//----------------------------------

using namespace DirectX;

namespace Engine
{
	class D311Context : public Context
	{
	public:
		D311Context(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen);
		
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

		IDXGISwapChain* mSwapChain;
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
		ID3D11RenderTargetView* mRenderTargetView;
		ID3D11Texture2D* mDepthStencilBuffer;
		ID3D11DepthStencilState* mDepthStencilState;
		ID3D11DepthStencilView* mDepthStencilView;
		ID3D11BlendState* mTransparant;
		ID3D11RasterizerState* mRasterState;

		XMMATRIX mWorldMatrix;
		XMMATRIX mOrthoMatrix;

		//TODO change name 
		std::vector<Sprite*> ThingsToRender;
		Sprite* mTempSprite;

		//Remove
		Sprite* TestSprite;
		Character* TestCharacter;

		TileMap testMap;


		// Render to texture for imgui
		ID3D11Texture2D* mRTTRrenderTargetTexture = nullptr;			// Texture to render to 
		ID3D11RenderTargetView* mRTTRenderTargetView = nullptr;		// Render target
		ID3D11ShaderResourceView* mRTTShaderResourceView = nullptr;	// Shader resource view for the texture

	};
}