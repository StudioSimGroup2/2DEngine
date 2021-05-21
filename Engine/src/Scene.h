#pragma once

#include <vector>

#include <Engine/Core.h>
#include <Engine/Renderer/Device.h>
#include <Entities/GameObject.h>
#include "Collision.h"

namespace Engine
{
	class ENGINE_API Scene
	{
	public:
		Scene();
		~Scene();

		void Init(); // When object is added to scene in editor mode
		void Start(); // When the scene starts
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();

		std::vector<GameObject*> GetSceneObjects() { return mSceneObjects; }

	private:
		std::vector<GameObject*> mSceneObjects;
		Collision collisionCheck;
	};
}

