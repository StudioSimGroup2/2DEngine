#pragma once

#include "Engine/Defines.h"

#if GRAPHICS_LIBRARY == 0 //DX11
#include "Backend/D3D11/D3D11Camera.h"
#elif GRAPHICS_LIBRARY == 1 // OpenGL
#include "Backend/OGL/OpenGLCamera.h"
#endif

#include <vector>
#include <assert.h>
#include <iostream>
#include <Utils\Math.h>
#include "Utils\Logger.h"



/** Singleton design pattern */
class CameraManager
{
public:
	static CameraManager* Get();
	~CameraManager();

	void Add(Camera* Camera);
	void Delete(size_t index);
	void Update(float deltaTime, bool forceUpdate=false); // force update, will force all the Cameras to be updated, not just the primary Camera
	void SetPrimaryCamera(size_t index);

	// Returns and sets the next active Camera to be either the next or previous Camera.
	Camera* CycleNext();
	Camera* CyclePrevious();
	static void CBCycleNext();
	static void CBCyclePrevious();


	Camera* GetPrimaryCamera() const;
	size_t GetPrimaryCameraIndex() const;
	Camera* GetCameraByIndex(size_t index) const;
	Camera* GetCameraByName(const std::string& Name) const;
	std::vector<Camera*> AllCameras() const { return mCameras; }


	static void Shutdown();

private:
	CameraManager() = default; // Create atleast 1 ortho Camera by default

	CameraManager(const CameraManager& other) = delete;
	void operator=(const CameraManager& other) = delete;

	static CameraManager* mInstance;
	std::vector<Camera*> mCameras;
};


