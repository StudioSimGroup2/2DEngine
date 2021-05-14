#include "CameraManager.h"


CameraManager* CameraManager::mInstance = nullptr;

CameraManager* CameraManager::Get()
{
	if (mInstance == nullptr)
		mInstance = new CameraManager();

	return mInstance;
}

CameraManager::~CameraManager()
{
	for (Camera* c : mCameras)
	{
		delete c;
		c = nullptr;
	}

	mCameras.shrink_to_fit();
}

void CameraManager::Add(Camera* Camera)
{
	mCameras.push_back(Camera);
	if (mCameras.size() == 1) 
		mCameras[0]->SetPrimary(true); // If this is the first Camera added, set it to be the primary Camera
}

void CameraManager::Delete(size_t index)
{
	ASSERT(!(index >= mCameras.size()), "CameraManager::Delete(), Index supplied was out of range");
	mCameras.erase(mCameras.begin() + index);
}

void CameraManager::Update(float deltaTime, bool forceUpdate)
{
	// Only update the primary camera
	for (Camera* c : mCameras) {
		if (forceUpdate) {
			c->Update(deltaTime);
			continue;
		}
		else if (c->IsPrimary()) {
			c->Update(deltaTime);
			break; // Break out of the loop as we can only have one primary camera
		}
	}
}

Camera* CameraManager::CycleNext()
{
	size_t range = mCameras.size();
	int currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
	if (++currentCamera >= range)
		currentCamera = 0;	// Wrap around when out of range

	CameraManager::Get()->SetPrimaryCamera(currentCamera);
	return mCameras[currentCamera];
}

Camera* CameraManager::CyclePrevious()
{
	int currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
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

	delete mInstance;
	mInstance = nullptr;
}

void CameraManager::CBCycleNext()
{
	size_t range = mInstance->mCameras.size();
	int currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
	if (++currentCamera >= range)
		currentCamera = 0;	// Wrap around when out of range

	CameraManager::Get()->SetPrimaryCamera(currentCamera);
}

void CameraManager::CBCyclePrevious()
{
	int currentCamera = CameraManager::Get()->GetPrimaryCameraIndex();
	if (--currentCamera < 0)
		currentCamera = mInstance->mCameras.size() - 1; // Wrap around when out of range

	CameraManager::Get()->SetPrimaryCamera(currentCamera);
}

Camera* CameraManager::GetPrimaryCamera() const
{
	for (Camera* c : mCameras) {
		if (c->IsPrimary())
			return c;
	}
	return nullptr;
}

size_t CameraManager::GetPrimaryCameraIndex() const
{
	for (size_t i = 0; i < mCameras.size(); i++) {
		if (mCameras[i]->IsPrimary())
			return i;
	}
	return 0;
}

