#include "GUILayer.h"
#include "imgui.h"
#include "imgui_stdlib.h"

#ifdef WINDOWS_PLATFORM
#include <Entry/WindowsSystem.h>
#endif

#include <Engine/Defines.h>

#if GRAPHICS_LIBRARY ==  1
#include "OpenGL/imgui_impl_win32_opengl.h"
#include "OpenGL/imgui_impl_opengl3.h"
#elif GRAPHICS_LIBRARY ==  0
#include "imgui_impl_win32.h"
#include "D3D11/imgui_impl_dx11.h"
#endif

#include <Engine/Renderer/Device.h>
#include <Engine/Application.h>

#include <ImFileDialog/ImFileDialog.h>
#include <implot/implot.h>
#include <CameraManager.h>

#include <SceneManager.h>


using namespace Engine;

GUILayer::GUILayer()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	Application* app = Application::GetInstance();
	io.DisplaySize = ImVec2(static_cast<float>(app->GetWindowData().GetWidth()), static_cast<float>(app->GetWindowData().GetHeight()));
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	//OpenGL version does not currently support viewports
#if GRAPHICS_LIBRARY ==  0
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 
#endif

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigDockingWithShift = true;

#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplWin32_Init(dynamic_cast<Engine::WindowsSystem*>(&app->GetWindowData())->GetHWND(), reinterpret_cast<void*>(Device::GetDevice()->GetHGLRC()));
	ImGui_ImplOpenGL3_Init("#version 460");
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
#endif
	};
}

GUILayer::~GUILayer()
{
	SceneManager::Shutdown();

	ifd::FileDialog::Instance().Close();

#if GRAPHICS_LIBRARY ==  1
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
#elif GRAPHICS_LIBRARY == 0
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
#endif

	ImPlot::DestroyContext();
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


#pragma region Menu Bar

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
				ifd::FileDialog::Instance().Open("File Browser", "Open a Project", "Engine Project File (*.prj){.png},.*");
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
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::MenuItem("Sprite"))
			{
			}
			if (ImGui::MenuItem("Audio File"))
			{
			}
			if (ImGui::MenuItem("Texture"))
			{
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo CTRL + Z"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Redo CTRL + Y"))
			{
				// No Impl
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Build"))
		{
			if (ImGui::MenuItem("Run"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Debug"))
			{
				// No Impl
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Asset Manager"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Console"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Inspector"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Scene Hierarchy"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Audio Manager"))
			{
				// No Impl
			}
			if (ImGui::MenuItem("Profiler"))
			{
				// No Impl
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				// No Impl
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

#pragma endregion

#pragma region Profiler

	ImS16 Default[3] = { 1, 1, 1 };
	ImS16 Renderer[3] = { 1, 1, 1 };
	ImS16 Assets[3] = { 1, 1, 1 };

	static const char* labels[] = { "Default", "Renderer", "Assets" };
	static const double positions[] = { 0, 1, 2 };

	ImGui::Begin("Profiler", NULL);
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Graphics Card Name: %s", Device::GetDeviceData().mGraphicsCardName.c_str());
	ImGui::Text("Estimated Total Memory: %iMB", Device::GetDeviceData().mGraphicsCardTotalMemory);
	ImGui::Text("Renderer API: %s", Device::GetDeviceData().mRendererAPI.c_str());
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Heap"))
	{
		ImPlot::SetNextPlotLimits(0, 110, -0.5, 9.5, ImGuiCond_Always);
		ImPlot::SetNextPlotTicksY(positions, 3, labels);

		if (ImPlot::BeginPlot("Heap Profiler", "Memory (MB)", "Heap",
			ImVec2(-1, 0), 0, 0, ImPlotAxisFlags_Invert))
		{
			ImPlot::SetLegendLocation(ImPlotLocation_West, ImPlotOrientation_Vertical);
			ImPlot::PlotBarsH("Default", Default, 3, 0.2, -0.2);
		}
		ImPlot::EndPlot();
	}
	ImGui::End();

#pragma endregion

#pragma region Logger


	if (true) {
		ImGui::Begin("Logger");

		std::string sen;
		for (std::string s : Logger::GetTextBuffer())	// Format the logs into one giant string... not ideal, as we cant do fancy colouring.
			sen += s;
		ImGui::Text("%s", sen.c_str());

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())	// Auto scroll to bottom
			ImGui::SetScrollHereY(1.0f);

		ImGui::End();
	}

	if (Logger::GetTextBuffer().size() > 512) { // Clear the console once it exceeds 512 logs
		Logger::GetTextBuffer().erase(Logger::GetTextBuffer().begin(), Logger::GetTextBuffer().begin() + 256);
	}


#pragma endregion

	//ImGui::ShowDemoWindow();

#pragma region SH // <------ Current Scene Hierarchy

	ImGui::Begin("Scene Hierarchy");
	static int selectionMask = (1 << 2);
	int sceneIndex = 0;
	int nodeClicked = -1;
	for (GameObject* go : SceneManager::GetInstance()->GetSceneObjects())
		CreateNode(go, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth, sceneIndex, nodeClicked, selectionMask);

	if (nodeClicked != -1)
	{
		// Update selection state
		// (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
		if (ImGui::GetIO().KeyCtrl)
			selectionMask ^= (1 << nodeClicked);          // CTRL+click to toggle
		else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
			selectionMask = (1 << nodeClicked);           // Click to single-select
	}

	//https://www.youtube.com/watch?v=Aog3mYBK7mA

	ImGui::End();

#pragma endregion 

#pragma region Inspector

	ImGui::Begin("Inspector");

	if (mCurrentSelectedNode != nullptr)
	{
		ImGui::Text(mCurrentSelectedNode->GetName().c_str());

		for (Component* c : mCurrentSelectedNode->GetComponents())
		{
			if (ImGui::CollapsingHeader(c->GetType().c_str()))
			{
				if (c->GetType() == "Transform")
				{
					TransformComponent(dynamic_cast<TransformComp*>(c));
				}
				else if (c->GetType() == "Sprite")
				{
					SpriteComponent(dynamic_cast<SpriteComp*>(c));
				}
				else if (c->GetType() == "Physics")
				{
					PhysicsComponent(dynamic_cast<PhysicsComp*>(c));
				}
				else if (c->GetType() == "TileMap")
				{
					TileMapComponent(dynamic_cast<TileMapComp*>(c));
				}
			}
		}
	}

	ImGui::End();

#pragma endregion


#pragma region Scene Hierarchy

	//ImGui::Begin("Scene Hierarchy");

	//ImGui::Separator();
	//ImGui::Text("Scene");
	//ImGui::Separator();

	//ImGui::Text("MARIO AND TILE MAP WILL GO HERE LATER!");
	//ImGui::Text("REQUIRES OTHERS TO EXPOSE DATA FOR ME");

	//int index = 0;
	////for (ParticleSystem* ps : mParticleSystems) {
	////	char label[20] = { 0 };
	////	sprintf_s(label, "Particle system %d", index);
	////	if (ImGui::TreeNode(label)) {
	////		ps->ShowEmmiterIcon(true);
	////		ImGui::Columns(2, "locations");
	////		ImGui::Text("Velocity");
	////		ImGui::Spacing();
	////		ImGui::Text("Emitter Position");
	////		ImGui::Spacing();
	////		ImGui::Spacing();
	////		ImGui::Text("Emitter Size");
	////		ImGui::Spacing();
	////		ImGui::Spacing();
	////		ImGui::Text("Emission Rate\n(seconds)");
	////		ImGui::Spacing();
	////		ImGui::Text("Gravity");
	////		ImGui::Spacing();
	////		ImGui::Text("Lifetime (seconds)");
	////		ImGui::Spacing();
	////		ImGui::Text("Texture");

	////		ImGui::NextColumn();

	////		ImGui::DragFloat2("##Velocity", &mParticleSystems[index]->GetVelocity().x, 1.0f);
	////		ImGui::DragFloat2("##Pos", &mParticleSystems[index]->GetPosition().x, 1.0f);
	////		ImGui::DragFloat2("##Size", &mParticleSystems[index]->GetSize().x, 1.0f);
	////		ImGui::DragFloat("##Rate", &mParticleSystems[index]->GetRate(), .025f);
	////		ImGui::Spacing();
	////		ImGui::Spacing();
	////		ImGui::Spacing();
	////		ImGui::DragFloat("##Gravity", &mParticleSystems[index]->GetGravity(), 1.0f);
	////		ImGui::DragFloat("##Lifetime", &mParticleSystems[index]->GetLifetime(), 0.25f);
	////		//ImGui::Image(, ImVec2(32,32)); // Sprite used in particle system

	////		ImGui::TreePop();
	////		ImGui::Columns();
	////	}
	////	else
	////		ps->ShowEmmiterIcon(false);

	////	index++;
	////}

	////Display Properties of Characters
	////index = 0;
	////for (Character* Characters : mGameScreenManager->getScreen()->GetCharacters())
	////{
	////	char label[256] = { 0 };
	////	sprintf_s(label, "Character: %s", Characters->GetName().c_str());
	////	if (ImGui::TreeNode(label)) {
	////		ImGui::TreePop();
	////	}
	////}

	//ImGui::Separator();
	//ImGui::Text("Cameras");
	//ImGui::Separator();

	//index = 0;
	//for (Camera* c : CameraManager::Get()->AllCameras()) {
	//	char label[10] = { 0 };
	//	sprintf_s(label, "Camera %d", index);
	//	if (ImGui::TreeNode(label)) {
	//		ImGui::Columns(2, "locations");
	//		ImGui::Text("Position");
	//		ImGui::Spacing();
	//		ImGui::Text("Z-Depth");
	//		ImGui::Spacing();
	//		ImGui::Text("Near plane");
	//		ImGui::Spacing();
	//		ImGui::Text("Far plane");
	//		ImGui::Spacing();
	//		ImGui::Text("Static camera");

	//		ImGui::NextColumn();

	//		//ImGui::DragFloat2("##Pos", &c->GetEye().x, 1);
	//		//ImGui::DragFloat("##Z-Depth", &c->GetZDepth(), 1, 0.0f);
	//		//ImGui::SliderFloat("##Near plane", &c->GetNearPlane(), 0, 10, "%.1f");
	//		//ImGui::SliderFloat("##Far plane", &c->GetFarPlane(), 1, 200, "%.1f");
	//		//ImGui::Checkbox("##Static camera", &c->IsStatic());

	//		ImGui::TreePop();
	//		ImGui::Columns();
	//	}
	//	index++;
	//}
	//ImGui::End();

#pragma endregion

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

void GUILayer::SpriteComponent(SpriteComp* c)
{
	ImGui::PushID("sprite");
 
	bool flipX = c->GetFlipX();
	bool flipY = c->GetFlipY();

	auto& ref = c->GetColour();

	std::string path;
	static ImVec4 colour = ImVec4(ref[0], ref[1],
		ref[2], ref[3]);

	if (c->GetTexture()->GetPath().length() > 25)
	{
		path = c->GetTexture()->GetPath().substr(25);
		path = path.substr(path.find_first_of('\\'));
	}
	else
	{
		path = c->GetTexture()->GetPath();
	}

	if (ImGui::Button(path.c_str()))
	{
		ifd::FileDialog::Instance().Open("File Browser", "LoadTileMap", "Texture File (*.png){.png},.*");
	}

	if (ifd::FileDialog::Instance().IsDone("File Browser"))
	{
		if (ifd::FileDialog::Instance().HasResult())
		{
			c->SetTexture(AssetManager::GetInstance()->LoadTexture(
				"", ifd::FileDialog::Instance().GetResult().u8string()));
		}
		ifd::FileDialog::Instance().Close();
	}

	ImGui::SameLine();
	ImGui::Image((void*)(intptr_t)c->GetTexID(), ImVec2(32.0f, 32.0f));

	ImGui::Text("Color");
	ImGui::SameLine();
	ImGui::ColorEdit4("##colpicker", (float*)&colour, ImGuiColorEditFlags_NoDragDrop);

	ImGui::Columns(2);
	ImGui::Text("Flip");
	ImGui::NextColumn();
	ImGui::Checkbox("X", &flipX);
	ImGui::SameLine();
	ImGui::Checkbox("Y", &flipY);
	ImGui::Columns(1);
	
	c->ToggleFlipX(flipX);
	c->ToggleFlipY(flipY);
	c->SetColour(colour.x, colour.y, colour.z, colour.w);


	ImGui::PopID();
}

void GUILayer::TransformComponent(TransformComp* c)
{
	float position[2];
	position[0] = c->GetPosition().x;
	position[1] = c->GetPosition().y;

	float scale[2] = { c->GetScale().x, c->GetScale().y };

	float rotation[2] = { c->GetRotation().x, c->GetRotation().y };
	
	ImGui::PushID("position");

	ImGui::Columns(2);
	ImGui::Text("Position");
	ImGui::NextColumn();
	ImGui::DragFloat2("##position", &position[0], 0.1f);
	ImGui::Columns(1);

	ImGui::PopID();

	ImGui::PushID("rotation");

	ImGui::Columns(2);
	ImGui::Text("Rotation");
	ImGui::NextColumn();
	ImGui::DragFloat2("##rotation", &rotation[0], 0.1f);
	ImGui::Columns(1);

	ImGui::PopID();

	ImGui::PushID("scale");

	ImGui::Columns(2);
	ImGui::Text("Scale");
	ImGui::NextColumn();
	ImGui::DragFloat2("##scale", &scale[0], 0.1f);
	ImGui::Columns(1);

	ImGui::PopID();

	c->SetPosition(position[0], position[1]);
	c->SetRotation(rotation[0], rotation[1]);
	c->SetScale(scale[0], scale[1]);
}

void GUILayer::PhysicsComponent(PhysicsComp* c)
{
	float physMass = c->GetMass();
	float physGrav = c->GetGravity();
	float physFric = c->GetFriction();

	ImGui::PushID("mass");

	ImGui::Columns(2);
	ImGui::Text("Mass");
	ImGui::NextColumn();
	ImGui::DragFloat("##mass", &physMass, 0.1f);
	ImGui::Columns(1);

	ImGui::PopID();

	ImGui::PushID("gravity");

	ImGui::Columns(2);
	ImGui::Text("Gravity");
	ImGui::NextColumn();
	ImGui::DragFloat("##gravity", &physGrav, 0.1f);
	ImGui::Columns(1);

	ImGui::PopID();

	ImGui::PushID("friction");

	ImGui::Columns(2);
	ImGui::Text("Friction");
	ImGui::NextColumn();
	ImGui::DragFloat("##friction", &physFric, 0.1f);
	ImGui::Columns(1);

	ImGui::PopID();

	c->SetMass(physMass);
	c->SetGravity(physGrav);
	c->SetFriction(physFric);
}

void GUILayer::TileMapComponent(TileMapComp* c)
{
	ImGui::PushID("TileMap");

	ImGui::Begin("Tile Editor");
	/*static int selectionMask = (1 << 2);
	int sceneIndex = 0;
	int nodeClicked = -1;*/
	static int TileID;
	for (int i = 0; i < AssetManager::GetInstance()->GetAllTextures()->size(); i++) {
		int  nhgfdjhgfdj = 0;
		auto tex = AssetManager::GetInstance()->GetAllTextures()->at(i);
		ImGui::PushID(i);
		if (ImGui::ImageButton((void*)(intptr_t)tex->GetTexID(), ImVec2(tex->GetWidth(), tex->GetHeight())))
		{
			TileID = i + 1;

		}
		ImGui::SameLine();

		//if (nodeClicked != -1)
		//{
		//	// Update selection state
		//	// (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
		//	if (ImGui::GetIO().KeyCtrl)
		//		selectionMask ^= (1 << nodeClicked);          // CTRL+click to toggle
		//	else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
		//		selectionMask = (1 << nodeClicked);           // Click to single-select
		//}
		ImGui::PopID();
	}
	//find mouse pos in world space

	ImGui::End();

	if (ImGui::Button("Load TileMap"))
	{
		ifd::FileDialog::Instance().Open("TileMapLoader", "LoadTileMap", "TileMap (*.xml){.xml},.*");
	}

	if (ifd::FileDialog::Instance().IsDone("TileMapLoader"))
	{
		if (ifd::FileDialog::Instance().HasResult())
		{
			std::string TempString = ifd::FileDialog::Instance().GetResult().u8string();
			c->LoadTileMap(TempString.c_str());
			TileMap temp = c->GetTileMap();
		}
		ifd::FileDialog::Instance().Close();
	}

	if (ImGui::Button("Save TileMap"))
	{
		ifd::FileDialog::Instance().Save("TileMapSaver", "LoadTileMap", "Texture File, (*.xml) {.xml}, .*");
	}

	if (ifd::FileDialog::Instance().IsDone("TileMapSaver"))
	{
		if (ifd::FileDialog::Instance().HasResult())
		{
			std::string TempString = ifd::FileDialog::Instance().GetResult().u8string();
			c->SaveTileMap(ifd::FileDialog::Instance().GetResult().u8string());
		}
		ifd::FileDialog::Instance().Close();
	}
	vec2f mousePos = vec2f(InputManager::GetInstance()->GetMousePosition().x, InputManager::GetInstance()->GetMousePosition().y);
	Logger::LogMsg("Mouse pos X:", mousePos.x);
	Logger::LogMsg("Mouse pos Y:", mousePos.y);
	ImGui::PopID();
}

void GUILayer::CreateNode(GameObject* go, int flags, int& index, int& nodeClicked, int& selectionMask)
{
	ImGui::PushID(index);
	ImGuiTreeNodeFlags node_flags = flags;
	const bool is_selected = (selectionMask & (1 << index)) != 0;
	if (is_selected)
		node_flags |= ImGuiTreeNodeFlags_Selected;

	bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)index, node_flags, go->GetName().c_str());

	if (ImGui::IsItemClicked())
	{
		nodeClicked = index;
		mCurrentSelectedNode = go;
	}

	if (node_open)
	{
		for (GameObject* child : go->GetChildren())
		{
			index++;
			CreateNode(child, flags, index, nodeClicked, selectionMask);
		}

		ImGui::TreePop();
	}
	ImGui::PopID();
	index++;
}

