#include "CameraManager.h"

#if GRAPHICS_LIBRARY == 0 //DX11
#include "Backend/D3D11/D3D11Camera.h"
#elif GRAPHICS_LIBRARY == 1 // OpenGL
#include "Backend/OGL/OpenGLCamera.h"
#endif

namespace Engine
{
	CameraManager* CameraManager::mInstance = nullptr;

	CameraManager* CameraManager::Get()
	{
		if (mInstance == nullptr)
			mInstance = new CameraManager();

		return mInstance;
	}

	CameraManager::~CameraManager()
	{
	}

	Camera* CameraManager::Add(vec2f pos, bool isEditorCamera)
	{
#if GRAPHICS_LIBRARY == 0 //DX11
		D3DCamera* camera = new D3DCamera(glm::vec4(pos.x, pos.y, 0.0f, 0.0f));
#elif GRAPHICS_LIBRARY == 1 // OpenGL
		OGLCamera* camera = new OGLCamera(glm::vec4(pos.x, pos.y, 0.0f, 0.0f));
#endif

		if (isEditorCamera)
			camera->SetEditorCamera(true);

		mCameras.push_back(camera);

		if (mCameras.size() == 1)
			mCameras[0]->SetPrimary(true); // If this is the first Camera added, set it to be the primary Camera

		return camera;
	}

	void CameraManager::Delete(size_t index)
	{
		ASSERT(!(index >= mCameras.size()), "CameraManager::Delete(), Index supplied was out of range");
		mCameras.erase(mCameras.begin() + index);
	}

	void CameraManager::Update(float deltaTime, bool forceUpdate)
	{
		if (!forceUpdate)
		{
			for (Camera* c : mCameras) {
				if (c->GetIsEditorCamera())
					c->Update(deltaTime);
			}
		}
		else
		{
			for (Camera* c : mCameras) {
				c->Update(deltaTime);
			}
		}
	}

	Camera* CameraManager::CycleNext()
	{
		size_t range = mCameras.size();
		size_t currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
		if (++currentCamera >= range)
			currentCamera = 0;	// Wrap around when out of range

		CameraManager::Get()->SetPrimaryCamera(currentCamera);
		return mCameras[currentCamera];
	}

	Camera* CameraManager::CyclePrevious()
	{
		size_t currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
		if (--currentCamera < 0)
			currentCamera = mCameras.size() - 1; // Wrap around when out of range

		CameraManager::Get()->SetPrimaryCamera(currentCamera);
		return mCameras[currentCamera];
	}

	Camera* CameraManager::GetCameraByIndex(size_t index) const
	{
		ASSERT(!(index >= mCameras.size()), "CameraManager::GetCameraByIndex(), Index supplied was out of range");
		return mCameras[index];
	}

	Camera* CameraManager::GetCameraByName(const std::string& Name) const
	{
		for (Camera* c : mCameras) {
			if (strcmp(c->GetName().c_str(), Name.c_str()) == 0)
				return c;
		}
		std::string errMsg = "CameraManager::GetCameraByName(), Could not find Camera with name supplied: '" + Name + "'";
		Logger::LogError(errMsg.c_str(), __FILE__);
		return nullptr;
	}

	void CameraManager::SetPrimaryCamera(size_t index)
	{
		size_t previouslyActive = CameraManager::Get()->GetPrimaryCameraIndex();
		mCameras[previouslyActive]->SetPrimary(false);
		mCameras[index]->SetPrimary(true);
	}

	void CameraManager::Shutdown()
	{
		if (mInstance == nullptr)
			return;

		for (Camera* c : mInstance->mCameras)
		{
			delete c;
			c = nullptr;
		}
		mInstance->mCameras.clear();
		delete mInstance;
		mInstance = nullptr;
	}

	void CameraManager::CBCycleNext()
	{
		if (mInstance->mCameras.size() <= 1)
			return;

		size_t range = mInstance->mCameras.size();
		size_t currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
		if (++currentCamera >= range)
			currentCamera = 0;	// Wrap around when out of range

		CameraManager::Get()->SetPrimaryCamera(currentCamera);
	}

	void CameraManager::CBCyclePrevious()
	{
		if (mInstance->mCameras.size() <= 1)
			return;

		size_t currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
		if ((currentCamera - 1) < 0)
			currentCamera = mInstance->mCameras.size() - 1; // Wrap around when out of range

		CameraManager::Get()->SetPrimaryCamera(currentCamera);
	}

	Camera* CameraManager::GetPrimaryCamera() const
	{
		for (Camera* c : mCameras) {
			if (c->GetIsPrimary())
				return c;
		}
		return nullptr;
	}

	size_t CameraManager::GetPrimaryCameraIndex() const
	{
		for (size_t i = 0; i < mCameras.size(); i++) {
			if (mCameras[i]->GetIsPrimary())
				return i;
		}
		return 0;
	}
}
