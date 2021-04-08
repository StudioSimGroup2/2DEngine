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

// [TEMP] Simple assert macro, move to pch file or smth later plz <3
#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }

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

	void LerpCameraTo(Camera* cam, vec2f toPos, float duration);


	Camera* GetPrimaryCamera() const;
	size_t GetPrimaryCameraIndex() const;
	Camera* GetCameraByIndex(size_t index) const;
	Camera* GetCameraByName(const std::string& Name) const;
	std::vector<Camera*> AllCameras() const { return mCameras; }


private:
	CameraManager() = default; // Create atleast 1 ortho Camera by default

	CameraManager(const CameraManager& other) = delete;
	void operator=(const CameraManager& other) = delete;

	// Move these to a math class later?
	float Lerpf(float a, float b, float t);
	vec2f Lerp2f(vec2f a, vec2f b, float t);

	static CameraManager* mInstance;
	std::vector<Camera*> mCameras;
};


