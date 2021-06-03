#pragma once

#include <vector>

#include <Engine/Core.h>
#include <Engine/Renderer/Device.h>
#include <Entities/GameObject.h>

#include "Entities/Components/ParticalSystem.h"

namespace Engine
{
	class ENGINE_API Scene
	{
	public:
		Scene();
		~Scene();

		void Init(); 
		void Start(); 
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();

		std::vector<GameObject*> GetSceneObjects() { return mSceneObjects; }

	private:
		std::vector<GameObject*> mSceneObjects;


	};
}

