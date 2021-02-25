#include "src/pch.h"
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
		delete c;
	mCameras.clear();

	if (mInstance != nullptr)
		delete mInstance;
}

void CameraManager::Add(Camera* camera)
{
	mCameras.push_back(camera);
	if (mCameras.size() == 1) 
		mCameras[0]->SetPrimary(true); // If this is the first camera added, set it to be the primary camera
}

void CameraManager::Delete(size_t index)
{
	ASSERT(!(index >= mCameras.size()), "Deleting camera, Index supplied was out of range");
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
	int currentCam = CameraManager::Get()->GetPrimaryCameraIndex();
	if (++currentCam >= range)
		currentCam = 0;	// Wrap around when out of range

	CameraManager::Get()->SetPrimaryCamera(currentCam);
	return mCameras[currentCam];
}

Camera* CameraManager::CyclePrevious()
{
	int currentCam = CameraManager::Get()->GetPrimaryCameraIndex();
	if (--currentCam < 0)
		currentCam = mCameras.size() - 1; // Wrap around when out of range

	CameraManager::Get()->SetPrimaryCamera(currentCam);
	return mCameras[currentCam];
}

Camera* CameraManager::GetCameraByIndex(size_t index) const
{
	ASSERT(!(index >= mCameras.size()), "Getting camera, Index supplied was out of range");
	return mCameras[index];
}

void CameraManager::SetPrimaryCamera(size_t index)
{
	size_t previouslyActive = CameraManager::Get()->GetPrimaryCameraIndex();
	mCameras[previouslyActive]->SetPrimary(false);
	mCameras[index]->SetPrimary(true);
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

