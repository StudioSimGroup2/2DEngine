#pragma once
#include "Camera.h"
#include <vector>
#include <assert.h>
#include <iostream>

// [TEMP] Simple assert macro, move to pch file or smth later plz <3
#define ASSERT(cond, msg) if (!cond) { std::cerr << "Assert failed: " << msg << ".\nFile: " << __FILE__ << ", line: " << __LINE__ << std::endl; abort(); }

/** Singleton design pattern */
class CameraManager
{
public:
	static CameraManager* Get();
	~CameraManager();

	inline void Add(Camera* camera) { mCameras.push_back(camera); }

	inline std::vector<Camera*> Cameras() const { return mCameras; }
	Camera* Cameras(size_t index) const;

private:
	CameraManager() = default; // Create atleast 1 ortho camera by default

	CameraManager(const CameraManager& other) = delete;
	void operator=(const CameraManager& other) = delete;

	static CameraManager* mInstance;
	std::vector<Camera*> mCameras;
};


