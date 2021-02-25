#pragma once
#include "Camera.h"

/** Singleton design pattern */
class CameraManager
{
public:
	static CameraManager* Get();
	~CameraManager();

	void Add(Camera* camera);
	void Delete(size_t index);
	void Update(float deltaTime, bool forceUpdate=false); // force update, will force all the cameras to be updated, not just the primary camera

	// Returns and sets the next active camera to be either the next or previous camera.
	Camera* CycleNext();
	Camera* CyclePrevious();

	Camera* GetPrimaryCamera() const;
	size_t GetPrimaryCameraIndex() const;
	Camera* GetCameraByIndex(size_t index) const;
	std::vector<Camera*> AllCameras() const { return mCameras; }

	void SetPrimaryCamera(size_t index);

private:
	CameraManager() = default; // Create atleast 1 ortho camera by default

	CameraManager(const CameraManager& other) = delete;
	void operator=(const CameraManager& other) = delete;

	static CameraManager* mInstance;
	std::vector<Camera*> mCameras;
};


