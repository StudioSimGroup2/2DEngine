#pragma once
#include "../Component.h"

#include "Engine/Camera.h"

namespace Engine
{
	class ENGINE_API CameraComp : public Component
	{
	public:
		CameraComp();
		CameraComp(GameObject* parent);
		~CameraComp() override;

		// Inherited via Component
		virtual void Start() override;

		virtual void Update() override;

		virtual void Render() override;

		virtual void InternalUpdate() override;

		virtual void InternalRender() override;


	private:
		void Init();

		Camera* mCamera = nullptr;

	};
}
