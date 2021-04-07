#include "GUILayer.h"
#include "imgui.h"

#ifdef WINDOWS_PLATFORM
#include <Entry/WindowsSystem.h>
#endif

#include <Engine/Defines.h>

#if GRAPHICS_LIBRARY ==  1
#include "Glad/glad.h"
#include "OpenGL/imgui_impl_win32_opengl.h"
#include "OpenGL/imgui_impl_opengl3.h"
#elif GRAPHICS_LIBRARY ==  0
#include "imgui_impl_win32.h"
#include "D3D11/imgui_impl_dx11.h"
#endif

#include <Engine/Renderer/Device.h>
#include <Engine/Application.h>

using namespace Engine;

GUILayer::GUILayer()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	Application* app = Application::GetInstance();
	io.DisplaySize = ImVec2(app->GetWindowData().GetWidth(), app->GetWindowData().GetHeight());
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	//OpenGL version does not currently support viewports
#if GRAPHICS_LIBRARY ==  0
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 
#endif

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigDockingWithShift = true;

#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplWin32_Init(static_cast<Engine::WindowsSystem*>(&app->GetWindowData())->GetHWND(), reinterpret_cast<void*>(Device::GetDevice()->GetHGLRC()));
	ImGui_ImplOpenGL3_Init("#version 460");
#elif GRAPHICS_LIBRARY ==  0
	ImGui_ImplWin32_Init(static_cast<Engine::WindowsSystem*>(&app->GetWindowData())->GetHWND());
	ImGui_ImplDX11_Init(Device::GetDevice()->GetDevice(), Device::GetDevice()->GetDeviceContext());
#endif

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
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
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Project CTRL + N")) {
				// No Impl
			}
			if (ImGui::MenuItem("Open Project CTRL + O"))
			{
				//ifd::FileDialog::Instance().Open("File Browser", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
			}
			if (ImGui::MenuItem("Save Project CTRL + S"))
			{
				//ifd::FileDialog::Instance().Open("File Browser", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
			}
			if (ImGui::MenuItem("Save Project As CTRL + SHIFT + S"))
			{

			}
			if (ImGui::MenuItem("Recent Projects"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Import Project"))
			{

			}
			if (ImGui::MenuItem("Export Project"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Preferences"))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit"))
			{

			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo CTRL + Z")) {
				// No Impl
			}
			if (ImGui::MenuItem("Redo CTRL + Y")) {
				// No Impl
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Build"))
		{
			if (ImGui::MenuItem("Run")) {
				// No Impl
			}
			if (ImGui::MenuItem("Debug")) {
				// No Impl
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Asset Manager")) {
				// No Impl
			}
			if (ImGui::MenuItem("Console")) {
				// No Impl
			}
			if (ImGui::MenuItem("Inspector")) {
				// No Impl
			}
			if (ImGui::MenuItem("Scene Hierarchy")) {
				// No Impl
			}
			if (ImGui::MenuItem("Audio Manager")) {
				// No Impl
			}
			if (ImGui::MenuItem("Profiler"))
			{

			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::ShowDemoWindow();

	ImGui::Begin("Framerate", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Render();

#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif GRAPHICS_LIBRARY == 0
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

#ifdef WINDOWS_PLATFORM
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
#endif
}

void GUILayer::Update()
{
}
