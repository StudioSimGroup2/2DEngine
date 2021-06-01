#include "GUILayer.h"
#include "imgui.h"
#include "imgui_stdlib.h"

#ifdef WINDOWS_PLATFORM
#include <Entry/WindowsSystem.h>
#endif

#include <Engine/Defines.h>

#include "imgui_impl_win32.h"
#if GRAPHICS_LIBRARY ==  1
#include "OpenGL/imgui_impl_opengl3.h"
#ifdef _WIN64

struct RendererData
{
	HDC hDC;
};

bool CreateDeviceOpenGL2(HWND hWnd, RendererData* data);
void CleanupDeviceOpenGL2(HWND hWnd, RendererData* data);
bool ActivateOpenGL2(HWND hWnd);
#endif
#elif GRAPHICS_LIBRARY ==  0
#include "D3D11/imgui_impl_dx11.h"
#endif

#include <Engine/Renderer/Device.h>
#include <Engine/Application.h>

#include <ImFileDialog/ImFileDialog.h>

#include <SceneManager.h>
#include <imgui_internal.h>

#include "LightingManager.h"

using namespace Engine;

GUILayer::GUILayer()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	Application* app = Application::GetInstance();
	io.DisplaySize = ImVec2(static_cast<float>(app->GetWindowData().GetWidth()), static_cast<float>(app->GetWindowData().GetHeight()));
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigDockingWithShift = true;
	io.IniFilename = "imgui.ini";

#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplWin32_Init(dynamic_cast<Engine::WindowsSystem*>(&app->GetWindowData())->GetHWND(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();

		// Store the hdc for this new window
		assert(platform_io.Renderer_CreateWindow == NULL);
		platform_io.Renderer_CreateWindow = Win32_CreateWindow;
		assert(platform_io.Renderer_DestroyWindow == NULL);
		platform_io.Renderer_DestroyWindow = Win32_DestroyWindow;
		assert(platform_io.Renderer_SwapBuffers == NULL);
		platform_io.Renderer_SwapBuffers = Win32_SwapBuffers;

		// We need to activate the context before drawing
		assert(platform_io.Platform_RenderWindow == NULL);
		platform_io.Platform_RenderWindow = Win32_RenderWindow;
	}
#elif GRAPHICS_LIBRARY ==  0
	ImGui_ImplWin32_Init(dynamic_cast<Engine::WindowsSystem*>(&app->GetWindowData())->GetHWND());
	ImGui_ImplDX11_Init(Device::GetDevice()->GetDevice(), Device::GetDevice()->GetDeviceContext());
#endif

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void*
	{
#if GRAPHICS_LIBRARY ==  1
		GLuint tex;

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
#elif GRAPHICS_LIBRARY ==  0
		ID3D11ShaderResourceView* tex;

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		D3D11_SUBRESOURCE_DATA srd;
		ZeroMemory(&srd, sizeof(srd));
		ID3D11Texture2D* tex2d = nullptr;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));

		desc.Width = static_cast<UINT>(w);
		desc.Height = static_cast<UINT>(h);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		srd.pSysMem = data;
		srd.SysMemPitch = static_cast<UINT>(4 * w);
		srd.SysMemSlicePitch = 0;

		Device::GetDevice()->GetDevice()->CreateTexture2D(&desc, &srd, &tex2d);

		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;

		Device::GetDevice()->GetDevice()->CreateShaderResourceView(tex2d, &srvDesc, &tex);
#endif
		return (void*)(size_t)tex;
	};

	ifd::FileDialog::Instance().DeleteTexture = [](void* tex)
	{
#if GRAPHICS_LIBRARY ==  1
		GLuint texID = (GLuint)(uintptr_t)(tex);
		glDeleteTextures(1, &texID);
#elif GRAPHICS_LIBRARY ==  0
		auto* srv = (ID3D11ShaderResourceView*)tex;

		srv->Release();
		srv = nullptr;
#endif
	};

	std::filesystem::path p = std::filesystem::current_path().parent_path();
	p /= "Engine\\Assets\\Editor\\Icons\\";
	AssetManager::GetInstance()->LoadTexture("PlayIcon", p.string() + "right.png");
	AssetManager::GetInstance()->LoadTexture("StopIcon", p.string() + "stop.png");
}

GUILayer::~GUILayer()
{
	SceneManager::Shutdown(); // This shouldn't be here

	ifd::FileDialog::Instance().Close();

#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
#elif GRAPHICS_LIBRARY == 0
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
#endif

	ImGui::DestroyContext();
}

void GUILayer::Render()
{
#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplOpenGL3_NewFrame();
#elif GRAPHICS_LIBRARY ==  0
	ImGui_ImplDX11_NewFrame();
#endif

#ifdef WINDOWS_PLATFORM
	ImGui_ImplWin32_NewFrame();
#endif

	ImGui::NewFrame();

	ImGui::SetNextWindowBgAlpha(1);
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	mMenuBar.Render();
	mProfiler.Render();


#pragma region GUI Buttons //Fix dockspace issues

	//float width = ImGui::GetMainViewport()->Size.x;
	//ImVec2 pos = ImGui::GetMainViewport()->Pos;
	//pos.y += menuBar;
	//ImGui::SetNextWindowPos(pos);
	//ImGui::SetNextWindowSize(ImVec2(width, 0.0f));

	//ImGui::Begin("GUIButtons", NULL, ImGuiWindowFlags_NoScrollbar |
	//	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	//ImGui::SetCursorPosX(width / 2);

	//if (ImGui::ImageButton((void*)(intptr_t)AssetManager::GetInstance()->GetTextureByName("PlayIcon")->GetTexID(), 
	//	ImVec2(16.0f, 16.0f)))
	//{

	//}
	//ImGui::SameLine();
	//if (ImGui::ImageButton((void*)(intptr_t)AssetManager::GetInstance()->GetTextureByName("StopIcon")->GetTexID(),
	//	ImVec2(16.0f, 16.0f)))
	//{

	//}

	//ImGui::End();

#pragma endregion

#pragma region Lighting
	ImGui::Begin("LightingDebug", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::MenuItem("Play"))
		{
			SceneManager::GetInstance()->DisableEditorMode();
			SceneManager::GetInstance()->PlayScene();
		}

		if (ImGui::MenuItem("Stop"))
		{
			SceneManager::GetInstance()->EnableEditorMode();
		}

		ImGui::SameLine(ImGui::GetContentRegionAvailWidth());
		SceneManager::GetInstance()->GetRunTime() ? ImGui::Text("Stopped") : ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), "Playing");
	}
	ImGui::EndMenuBar();

#if GRAPHICS_LIBRARY ==  1
	ImGui::Image((void*)(intptr_t)SceneManager::GetInstance()->GetRenderToTexID(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
#elif GRAPHICS_LIBRARY == 0
	ImGui::Image((void*)(intptr_t)LightingManager::GetInstance()->GetRenderToTexID(), ImGui::GetContentRegionAvail());
#endif

	ImGui::End();
#pragma endregion

#pragma region
	SceneManager::GetInstance()->HasUserNotSaved() ? ImGui::Begin("Game*", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar)
		: ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::MenuItem("Play")) 
		{
			SceneManager::GetInstance()->DisableEditorMode();
			SceneManager::GetInstance()->PlayScene();
		}

		if (ImGui::MenuItem("Stop")) 
		{
			SceneManager::GetInstance()->EnableEditorMode();
		}

		ImGui::SameLine(ImGui::GetContentRegionAvailWidth());
		SceneManager::GetInstance()->GetRunTime() ? ImGui::Text("Stopped") : ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), "Playing");
	}
	ImGui::EndMenuBar();

	ImVec2 gameScreenA = { ImGui::GetWindowContentRegionMin().x + ImGui::GetWindowPos().x, ImGui::GetWindowContentRegionMin().y + ImGui::GetWindowPos().y };
	ImVec2 gameScreenB = { ImGui::GetWindowContentRegionMax().x + ImGui::GetWindowPos().x, ImGui::GetWindowContentRegionMax().y + ImGui::GetWindowPos().y };

	ImVec2 mouseOffset = ImGui::GetMousePos();
	ImVec2 mouseOffsetA = ImGui::GetMousePos();

	mouseOffset.x -= gameScreenA.x;
	mouseOffset.y -= gameScreenA.y;

	if (mouseOffset.x < 0.0f)
		mouseOffset.x = 0.0f;

	if (mouseOffset.y < 0.0f)
		mouseOffset.y = 0.0f;

	if (mouseOffset.x > (gameScreenB.x - gameScreenA.x))
		mouseOffset.x = gameScreenB.x - gameScreenA.x;

	if (mouseOffset.y > (gameScreenB.y - gameScreenA.y))
		mouseOffset.y = gameScreenB.y - gameScreenA.y;

	InputManager::GetInstance()->SetMouseScreenPosition(vec2f(mouseOffset.x, mouseOffset.y));
	vec2f WindowSize = vec2f(ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y);
	vec2f renderSize = vec2f(gameScreenB.x - gameScreenA.x , gameScreenB.y - gameScreenA.y);
	InputManager::GetInstance()->SetScreenSizePercent(WindowSize, renderSize);
	InputManager::GetInstance()->SetScreenSize(renderSize);

#if GRAPHICS_LIBRARY ==  1
	ImGui::Image((void*)(intptr_t)SceneManager::GetInstance()->GetRenderToTexID(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
#elif GRAPHICS_LIBRARY == 0
	ImGui::Image((void*)(intptr_t)SceneManager::GetInstance()->GetRenderToTexID(), ImGui::GetContentRegionAvail());
#endif

	ImGui::End();
#pragma endregion



	mSceneHierarchy.Render();
	mInspector.Render(SceneHierarchyWidget::GetNode());
	mLogger.Render();

	ImGui::Render();

#if GRAPHICS_LIBRARY ==  0
	//Device::GetDevice()->ClearAndSetRenderTarget();
#endif

#if GRAPHICS_LIBRARY ==  1
	GLint last_program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	glUseProgram(0);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glUseProgram(last_program);
#elif GRAPHICS_LIBRARY == 0
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

#ifdef WINDOWS_PLATFORM
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
#endif

#if GRAPHICS_LIBRARY ==  1
	wglMakeCurrent(Device::GetDevice()->GetHDC(), Device::GetDevice()->GetHGLRC());
#endif
}

void GUILayer::Update()
{
}

#if GRAPHICS_LIBRARY ==  1
void GUILayer::Win32_CreateWindow(ImGuiViewport* viewport)
{
	assert(viewport->RendererUserData == NULL);

	RendererData* data = IM_NEW(RendererData);
	CreateDeviceOpenGL2((HWND)viewport->PlatformHandle, data);
	viewport->RendererUserData = data;
}

bool CreateDeviceOpenGL2(HWND hWnd, RendererData* data)
{
	if (!ActivateOpenGL2(hWnd))
		return false;

	data->hDC = GetDC(hWnd);

	if (!Device::GetDevice()->GetHGLRC())
	{
		Device::GetDevice()->SetHGLRC(wglCreateContext(data->hDC));
	}

	return true;
}

bool ActivateOpenGL2(HWND hWnd)
{
	HDC hDc = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pixelFormatDesc;
	ZeroMemory(&pixelFormatDesc, sizeof(pixelFormatDesc));
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.dwFlags = LPD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits = 24;
	pixelFormatDesc.cDepthBits = 32;
	pixelFormatDesc.cStencilBits = 8;
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

	int pf = ChoosePixelFormat(hDc, &pixelFormatDesc);
	if (pf == 0)
	{
		return false;
	}

	if (SetPixelFormat(hDc, pf, &pixelFormatDesc) == FALSE)
	{
		return false;
	}

	ReleaseDC(hWnd, hDc);
	return true;
}

void GUILayer::Win32_RenderWindow(ImGuiViewport* viewport, void*)
{
	RendererData* data = (RendererData*)viewport->RendererUserData;

	if (data)
	{
		// Activate the platform window DC in the OpenGL rendering context
		wglMakeCurrent(data->hDC, Device::GetDevice()->GetHGLRC());
	}
}

void GUILayer::Win32_SwapBuffers(ImGuiViewport* viewport, void*)
{
	RendererData* data = (RendererData*)viewport->RendererUserData;

	if (data)
	{
		SwapBuffers(data->hDC);
	}
}

void GUILayer::Win32_DestroyWindow(ImGuiViewport* viewport)
{
	if (viewport->RendererUserData != NULL)
	{
		RendererData* data = (RendererData*)viewport->RendererUserData;
		CleanupDeviceOpenGL2((HWND)viewport->PlatformHandle, data);
		IM_DELETE(data);
		viewport->RendererUserData = NULL;
	}
}

void CleanupDeviceOpenGL2(HWND hWnd, RendererData* data)
{
	wglMakeCurrent(NULL, NULL);
	ReleaseDC(hWnd, data->hDC);
}
#endif

