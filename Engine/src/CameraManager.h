#pragma once

#include "Engine/Defines.h"

#include "Engine/Camera.h"

#include <vector>
#include <assert.h>
#include <iostream>
#include <Utils\Math.h>
#include "Utils\Logger.h"

/** Singleton design pattern */
namespace Engine
{
	class CameraManager
	{
	public:
		static CameraManager* Get();
		~CameraManager();

		Camera* Add(vec2f pos, bool isEditorCamera = false);

		void Delete(size_t index);
		void Update(float deltaTime, bool forceUpdate = false); // force update, will force all the Cameras to be updated, not just the primary Camera
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
}
