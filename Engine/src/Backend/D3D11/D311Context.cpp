#include "D311Context.h"
#include "D3D11Renderer2D.h"

#include <Utils/AssetManager.h>
#include <Engine/Audio/AudioManager.h>
#include <directxcolors.h>

#include <Backend/D3D11/D3D11Camera.h>
#include <Engine/Input/InputManager.h>

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
	}

	D311Context::~D311Context()
	{
		Shutdown();
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

		//---------------------------------
		//Render to texture (for ImGUI viewport)
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));  
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		mDevice->CreateTexture2D(&textureDesc, NULL, &mRTTRrenderTargetTexture);
		
		// Setup the description of the render target view.
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
		mDevice->CreateRenderTargetView(mRTTRrenderTargetTexture, &renderTargetViewDesc, &mRTTRenderTargetView);

		// Setup the description of the shader resource view.
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		mDevice->CreateShaderResourceView(mRTTRrenderTargetTexture, &shaderResourceViewDesc, &mRTTShaderResourceView);
		//---------------------------------

		// Setup ImGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(mScreenWidth, mScreenHeight);
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigDockingWithShift = true;
		//io.IniFilename = "..\\ImGui\\imgui.ini";
		ImGui_ImplWin32_Init(mHWND);
		ImGui_ImplDX11_Init(mDevice, mDeviceContext);
		ImGui::StyleColorsDark();


		// Create the viewport.
		mDeviceContext->RSSetViewports(1, &viewport);

		AssetManager::GetInstance();

		// Create two cameras
		CameraManager::Get()->Add(new Camera(XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f)));
		CameraManager::Get()->Add(new Camera(XMFLOAT4(-964.0f, 94.0f, -1.0f, 1.0f)));
		CameraManager::Get()->GetCameraByIndex(1)->SetStatic(true);

		Camera* cam = CameraManager::Get()->GetPrimaryCamera();

		InputManager::GetInstance()->BindCommandToButton(KEY_Q, &CameraManager::Get()->CBCycleNext);
		InputManager::GetInstance()->BindCommandToButton(KEY_E, &CameraManager::Get()->CBCyclePrevious);
		mDeviceMGR = new D3D11Device(mDevice, mDeviceContext);

 		AssetManager::GetInstance()->LoadShader(mDeviceMGR, std::string("Default"), std::string("quadshader.fx"));

		AudioManager::GetInstance()->LoadSound(std::string("TestFile"), std::string("Sounds/zip.wav"));
		//AudioManager::GetInstance()->PlaySoundFile(std::string("TestFile"), -100.0f); // TODO: implement volume WARNING THE SOUND FILE IS EXTREMELY LOUD!!

		testMap = LevelMap::LoadLevelMap((char*)"Resources/TileMaps/XML_Test.xml");
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
					Sprite* mapItem = new Sprite(mDeviceMGR, std::string("Tile ") + std::string(X + "" + Y) + std::string("]"), 
						std::string("Textures/stone.dds"), vec2f(32.0f * Y, 32.0f * X)); // someone got their x and y coords wrong, i'll fix it later
					D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDeviceMGR);
					mapItem->AddRendererComponent(re);

					ThingsToRender.push_back(mapItem);
					break;
				}
				default:
					break;
				}
			}
		}

		mTempSprite = new Sprite(mDeviceMGR, std::string("Mario"), std::string("Textures/Mario.dds"), vec2f(32.0f));
		D3D11Renderer2D* renderer = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDeviceMGR);
		mTempSprite->AddRendererComponent(renderer);


		// Particle Props Init	
		Sprite* particleTex = new Sprite(mDeviceMGR, "Partical Texture", "Resources\\Textures\\stone.dds", vec2f(0, 0));
		D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDeviceMGR);
		particleTex->AddRendererComponent(re);
		ParticleProperties prop(vec2f(100, -100), 3, particleTex);

		// Particle System Init
		mParticleSystems.emplace_back(new ParticleSystem(mDeviceMGR, vec2f(300, 300), prop, 150, Emmitter::Square));
		mParticleSystems[0]->SetGravity(100);
		mParticleSystems[0]->SetRate(0.1); // Particles per second
	}

	void D311Context::Shutdown()
	{
		if (ThingsToRender.size() >= 1)
		{
			ThingsToRender.clear();
		}

		for (ParticleSystem* ps : mParticleSystems)
			delete ps;
		mParticleSystems.clear();

		if (mTempSprite)
		{
			delete mTempSprite;
			mTempSprite = nullptr;
		}

		if (mDeviceMGR)
		{
			delete mDeviceMGR;
			mDeviceMGR = nullptr;
		}
			

		if (mRasterState)
			mRasterState->Release();
		if (mDepthStencilView)
			mDepthStencilView->Release();
		if (mDepthStencilBuffer)
			mDepthStencilBuffer->Release();
		if (mRenderTargetView)
			mRenderTargetView->Release();
		if (mDevice)
			mDevice->Release();
		if (mDeviceContext)
			mDeviceContext->Release();
		if (mSwapChain)
			mSwapChain->Release();
	}

	void D311Context::OnUpdate(float deltaTime)
	{
		CameraManager::Get()->Update(deltaTime);

		mTempSprite->Update(deltaTime);

		for (ParticleSystem* ps : mParticleSystems)
			ps->Update(deltaTime);
	}

	void D311Context::RenderScene()
	{
		mDeviceContext->ClearRenderTargetView(mRenderTargetView, DirectX::Colors::SeaGreen);

		for (auto Thing : ThingsToRender)
		{
			Thing->Draw();
		}
		mTempSprite->Draw();

		for (ParticleSystem* ps : mParticleSystems)
			ps->Render();

	}

	void D311Context::SwapBuffers()
	{
		mDeviceContext->OMSetRenderTargets(1, &mRTTRenderTargetView, mDepthStencilView);
		mDeviceContext->ClearRenderTargetView(mRTTRenderTargetView, DirectX::Colors::SeaGreen);
		RenderScene();

	
		mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView); // Set back to back buffer
		mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
		RenderScene();
		
		RenderImGui();

		mSwapChain->Present(0, 0);
	}

	void D311Context::RenderImGui()
	{
		// ImGui rendering below (Move to seperate UI rendering function later
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Create core dockspace
		ImGui::SetNextWindowBgAlpha(0);
		if (mEnableEditor) {
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.180392161f, 0.5450980663f, 0.3411764801f, 1.0f));  // THIS IS BECAUSE THERES TRANSPARENCY ISSUES ATM! NOT PERMANENT
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.180392161f, 0.5450980663f, 0.3411764801f, 1.0f)); 	 // THIS IS BECAUSE THERES TRANSPARENCY ISSUES ATM! NOT PERMANENT
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::Begin("Viewport", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::Image(mRTTShaderResourceView, ImGui::GetWindowContentRegionMax()); // render texture 
			ImGui::End();
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}
		
		// Menu
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New")) {
					// No Impl
				}
				if (ImGui::MenuItem("Open...")) {
					// No Impl
				}
				if (ImGui::MenuItem("Save As...")) {
					// No Impl
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Toggle Editor Layout")) {
					mEnableEditor = !mEnableEditor;
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::MenuItem("Sprite")) {
					// No Impl
				}
				if (ImGui::MenuItem("Particle system")) {
					// Particle Props Init	
					Sprite* particleTex = new Sprite(mDeviceMGR, "Partical Texture", "Resources\\Textures\\stone.dds", vec2f(0, 0));
					D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDeviceMGR);
					particleTex->AddRendererComponent(re);
					ParticleProperties prop(vec2f(0, 0), 3, particleTex);

					// Particle System Init
					ParticleSystem* temp = new ParticleSystem(mDeviceMGR, vec2f(0, 0), prop, 150, Emmitter::Square);
					temp->SetGravity(100);
					temp->SetRate(0.1); // Particles per second
					mParticleSystems.emplace_back(temp);
	
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}


		// Viewport
	

		//
		// TEMP
		//
		ImGui::Begin("Scene Hierarchy");

		ImGui::Separator();
		ImGui::Text("Scene");
		ImGui::Separator();

		ImGui::Text("MARIO AND TILE MAP WILL GO HERE LATER!");
		ImGui::Text("REQUIRES OTHERS TO EXPOSE DATA FOR ME");

		int index = 0;
		for (ParticleSystem* ps : mParticleSystems) {
			char label[20] = { 0 };
			sprintf_s(label, "Particle system %d", index);
			if (ImGui::TreeNode(label)) {
				ps->ShowEmmiterIcon(true);
				ImGui::Columns(2, "locations");
				ImGui::Text("Velocity");
				ImGui::Spacing();
				ImGui::Text("Emitter Position");
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("Emitter Size");
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("Emission Rate\n(seconds)");
				ImGui::Spacing();
				ImGui::Text("Gravity");
				ImGui::Spacing();
				ImGui::Text("Lifetime (seconds)");
				ImGui::Spacing();
				ImGui::Text("Texture");

				ImGui::NextColumn();

				ImGui::DragFloat2("##Velocity", &mParticleSystems[index]->GetVelocity().x, 1.0f);
				ImGui::DragFloat2("##Pos", &mParticleSystems[index]->GetPosition().x, 1.0f);
				ImGui::DragFloat2("##Size", &mParticleSystems[index]->GetSize().x, 1.0f);
				ImGui::DragFloat("##Rate", &mParticleSystems[index]->GetRate(), .025f);
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::DragFloat("##Gravity", &mParticleSystems[index]->GetGravity(), 1.0f);
				ImGui::DragFloat("##Lifetime", &mParticleSystems[index]->GetLifetime(), 0.25f);
				//ImGui::Image(, ImVec2(32,32)); // Sprite used in particle system

				ImGui::TreePop();
				ImGui::Columns();
			} else
				ps->ShowEmmiterIcon(false);

			index++;
		}

		ImGui::Separator();
		ImGui::Text("Cameras");
		ImGui::Separator();

		index = 0;
		for (Camera* c : CameraManager::Get()->AllCameras()) {
			char label[10] = { 0 };
			sprintf_s(label, "Camera %d", index);
			if (ImGui::TreeNode(label)) {
				ImGui::Columns(2, "locations");
				ImGui::Text("Position");
				ImGui::Spacing();
				ImGui::Text("Z-Depth"); 
				ImGui::Spacing();
				ImGui::Text("Near plane");
				ImGui::Spacing();
				ImGui::Text("Far plane"); 
				ImGui::Spacing();
				ImGui::Text("Static camera"); 
		
				ImGui::NextColumn();

				ImGui::DragFloat2("##Pos", &c->GetEye().x, 1);
				ImGui::DragFloat("##Z-Depth", &c->GetZDepth(), 1, 0.0f);
				ImGui::SliderFloat("##Near plane", &c->GetNearPlane(), 0, 10, "%.1f");
				ImGui::SliderFloat("##Far plane", &c->GetFarPlane(), 1, 200, "%.1f");
				ImGui::Checkbox("##Static camera", &c->IsStatic());

				ImGui::TreePop();
				ImGui::Columns();
			}
			index++;
		}
		ImGui::End();

		ImGui::Begin("Framerate");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}