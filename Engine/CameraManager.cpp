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


Camera* CameraManager::Cameras(size_t index) const
{
	ASSERT(index > mCameras.size() || index < 0, "Index supplied was out of range");
	return mCameras[index];
}

