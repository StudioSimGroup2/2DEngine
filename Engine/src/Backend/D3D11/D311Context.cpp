#include "../../pch.h"
#include "D311Context.h"
#include <directxcolors.h>

namespace Engine
{
	D311Context::D311Context(HWND hwnd, UINT32 screenWidth, UINT32 screenHeight, bool vSync, bool fullscreen)
	{
		mSwapChain = 0;
		mDevice = 0;
		mDeviceContext = 0;
		mRenderTargetView = 0;
		mDepthStencilBuffer = 0;
		mDepthStencilState = 0;
		mDepthStencilView = 0;
		mRasterState = 0;

		mHWND = hwnd;
		mScreenHeight = screenHeight;
		mScreenWidth = screenWidth;
		vSync = vSync;
	}

	void D311Context::Init()
	{
		HRESULT hr;

		IDXGIFactory* factory;
		IDXGIAdapter* adapter;
		IDXGIOutput* adapterOutput;
		unsigned int numModes, i, numerator, denominator;
		unsigned long long stringLength;
		DXGI_MODE_DESC* displayModeList;
		DXGI_ADAPTER_DESC adapterDesc;
		int error;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		D3D_FEATURE_LEVEL featureLevel;
		ID3D11Texture2D* backBufferPtr;
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		D3D11_RASTERIZER_DESC rasterDesc;
		D3D11_VIEWPORT viewport;
		float fieldOfView, screenAspect;

		// Need client rect insted of window res
		RECT rc;
		GetClientRect(mHWND, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		// Create a DirectX graphics interface factory.
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if (FAILED(hr))
		{
			return;
		}

		// Use the factory to create an adapter for the primary graphics interface (video card).
		hr = factory->EnumAdapters(0, &adapter);
		if (FAILED(hr))
		{
			return;
		}

		// Enumerate the primary adapter output (monitor).
		hr = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(hr))
		{
			return;
		}

		// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (FAILED(hr))
		{
			return;
		}

		// Create a list to hold all the possible display modes for this monitor/video card combination.
		displayModeList = new DXGI_MODE_DESC[numModes];
		if (!displayModeList)
		{
			return;
		}

		// Now fill the display mode list structures.
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
		if (FAILED(hr))
		{
			return;
		}

		// Now go through all the display modes and find the one that matches the screen width and height.
		// When a match is found store the numerator and denominator of the refresh rate for that monitor.
		for (i = 0; i < numModes; i++)
		{
			if (displayModeList[i].Width == (unsigned int)mScreenWidth)
			{
				if (displayModeList[i].Height == (unsigned int)mScreenHeight)
				{
					numerator = displayModeList[i].RefreshRate.Numerator;
					denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		// Get the adapter (video card) description.
		hr = adapter->GetDesc(&adapterDesc);
		if (FAILED(hr))
		{
			return;
		}

		// Store the dedicated video card memory in megabytes.
		mMemorySize = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

		// Convert the name of the video card to a character array and store it.
		char cardDesc[128];
		char defchar = ' ';

		WideCharToMultiByte(CP_ACP, 0, adapterDesc.Description, -1, cardDesc, 128, &defchar, NULL);

		mName = std::string(cardDesc);

		// Release the display mode list.
		delete[] displayModeList;
		displayModeList = 0;

		// Release the adapter output.
		adapterOutput->Release();
		adapterOutput = 0;

		// Release the adapter.
		adapter->Release();
		adapter = 0;

		// Release the factory.
		factory->Release();
		factory = 0;

		// Initialize the swap chain description.
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		// Set to a single back buffer.
		swapChainDesc.BufferCount = 1;

		// Set the width and height of the back buffer.
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;

		// Set regular 32-bit surface for the back buffer.
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// Set the refresh rate of the back buffer.
		if (true)
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		}
		else
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		}

		// Set the usage of the back buffer.
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		// Set the handle for the window to render to.
		swapChainDesc.OutputWindow = mHWND;

		// Turn multisampling off.
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		//// Set to full screen or windowed mode.
		//if(fullscreen)
		//{
		//	swapChainDesc.Windowed = false;
		//}

		swapChainDesc.Windowed = true;
		// Set the scan line ordering and scaling to unspecified.
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		// Discard the back buffer contents after presenting.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// Don't set the advanced flags.
		swapChainDesc.Flags = 0;

		// Set the feature level to DirectX 11.
		featureLevel = D3D_FEATURE_LEVEL_11_0;

		/*Create the swap chain, Direct3D device, and Direct3D device context.*/
		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, &featureLevel, 1,
			D3D11_SDK_VERSION, &swapChainDesc, &mSwapChain, &mDevice, NULL, &mDeviceContext);

		if (FAILED(hr))
		{
			return;
		}

		// Get the pointer to the back buffer.
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
		if (FAILED(hr))
		{
			return;
		}

		// Create the render target view with the back buffer pointer.
		hr = mDevice->CreateRenderTargetView(backBufferPtr, NULL, &mRenderTargetView);
		if (FAILED(hr))
		{
			return;
		}

		// Release pointer to the back buffer as we no longer need it.
		backBufferPtr->Release();
		backBufferPtr = 0;

		// Initialize the description of the depth buffer.
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		// Set up the description of the depth buffer.
		depthBufferDesc.Width = width;
		depthBufferDesc.Height = height;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		// Create the texture for the depth buffer using the filled out description.
		hr = mDevice->CreateTexture2D(&depthBufferDesc, NULL, &mDepthStencilBuffer);
		if (FAILED(hr))
		{
			return;
		}

		// Initialize the description of the stencil state.
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		// Set up the description of the stencil state.
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing.
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing.
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


		// Create the depth stencil state.
		hr = mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilState);
		if (FAILED(hr))
		{
			return;
		}

		// Set the depth stencil state.
		mDeviceContext->OMSetDepthStencilState(mDepthStencilState, 1);

		// Initialize the depth stencil view.
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		// Set up the depth stencil view description.
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		// Create the depth stencil view.
		hr = mDevice->CreateDepthStencilView(mDepthStencilBuffer, &depthStencilViewDesc, &mDepthStencilView);
		if (FAILED(hr))
		{
			return;
		}

		// Bind the render target view and depth stencil buffer to the output render pipeline.
		mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

		// Setup the raster description which will determine how and what polygons will be drawn.
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.DepthBias = 0; 
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state from the description we just filled out.
		hr = mDevice->CreateRasterizerState(&rasterDesc, &mRasterState);
		if (FAILED(hr))
		{
			return;
		}

		// Now set the rasterizer state.
		mDeviceContext->RSSetState(mRasterState);

		
		//---------------------------------
		//blending
		D3D11_BLEND_DESC omDesc;
		ZeroMemory(&omDesc, sizeof(D3D11_BLEND_DESC));
		omDesc.RenderTarget[0].BlendEnable = true;
		omDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		omDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		omDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		omDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		omDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		omDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		omDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		mDevice->CreateBlendState(&omDesc, &mTransparant);


		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		UINT sampleMask = 0xffffffff;
		mDeviceContext->OMSetBlendState(mTransparant, blendFactor, sampleMask);
		//----------------------------------

		// Setup the viewport for rendering.
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		// Setup ImGUI

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); // Currently dont need IO so commented out...
		ImGui_ImplWin32_Init(mHWND);
		ImGui_ImplDX11_Init(mDevice, mDeviceContext);
		ImGui::StyleColorsDark();


		// Create the viewport.
		mDeviceContext->RSSetViewports(1, &viewport);


		// Create two cameras
		CameraManager::Get()->Add(new Camera(XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f)));
		CameraManager::Get()->Add(new Camera(XMFLOAT4(-964.0f, 94.0f, -1.0f, 1.0f)));



		testMap = LevelMap::LoadLevelMap((char*)"TileMaps/FirstTest.txt");


		for (int X = 0; X <testMap.size(); X++)
		{
			for (int Y = 0; Y < testMap[0].size(); Y++)
			{
				switch (testMap[X][Y])
				{
				case 0:
				{
					break;
				}
				case 1:
				{
					Vector2D* Position = new Vector2D(Y * TILEWIDTH, X * TILEHEIGHT);
					Sprite* MapItem = new Sprite(mDevice, L"Textures/stone.dds", Position);
					ThingsToRender.push_back(MapItem);
					break;
				}
				default:
					break;
				}
			}
		}

		Vector2D* Position = new Vector2D(32, 32);
		TestCharacter = new Character(mDevice, L"Textures/Mario.dds", Position);
	}

	void D311Context::Shutdown()
	{
		mSwapChain->Release();
		mDevice->Release();
		mDeviceContext->Release();
	}

	void D311Context::OnUpdate(float deltaTime)
	{
		CameraManager::Get()->Update(deltaTime); // Belongs in core scene update loop

		// Cycle cameras on A & D keypresses 
		if (GetAsyncKeyState(0x51)) // Q key
			CameraManager::Get()->CyclePrevious();
		if (GetAsyncKeyState(0x45)) // E key
			CameraManager::Get()->CycleNext();


		if (GetAsyncKeyState(0x27)) //Right arrow
		{
			TestCharacter->setMovingRight(true);
		}
		else 
		{
			TestCharacter->setMovingRight(false);
		}	

		if (GetAsyncKeyState(0x25)) //Left arrow
		{
			TestCharacter->setMovingLeft(true);
		}
		else
		{
			TestCharacter->setMovingLeft(false);
		}

		TestCharacter->Update(deltaTime);
	}

	void D311Context::SwapBuffers()
	{
		mDeviceContext->ClearRenderTargetView(mRenderTargetView, DirectX::Colors::SeaGreen);

		for (auto Thing : ThingsToRender)
		{
			Thing->Render(mDeviceContext);
		}
		TestCharacter->Render(mDeviceContext);

		// ImGui rendering below (Move to seperate UI rendering function later
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Temp ImGui window!");
		ImGui::Text("Hello world!");
		ImGui::End();

		ImGui::Begin("Framerate");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		mSwapChain->Present(0, 0);
	}
}