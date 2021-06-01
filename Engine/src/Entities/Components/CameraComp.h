#pragma once
#include "../Component.h"

#include "Engine/Camera.h"

namespace Engine
{
	class ENGINE_API CameraComp : public Component
	{
	public:
		CameraComp();
		~CameraComp() override;

		void SetFOV(float fov) { mCamera->SetFOV(fov); }
		void SetNear(float cNear) { mCamera->SetNear(cNear); }
		void SetFar(float cFar) { mCamera->SetFar(cFar); }
		void SetDepth(float depth) { mCamera->SetDepth(depth); }

		float GetFOV() { return mCamera->GetFOV(); }
		float GetNear() { return mCamera->GetNear(); }
		float GetFar() { return mCamera->GetFar(); }
		float GetDepth() { return mCamera->GetDepth(); }

		// Inherited via Component
		virtual void Init() override;

		virtual void Start() override;

		virtual void Update() override;

		virtual void Render() override;

		virtual void InternalUpdate() override;

		virtual void InternalRender() override;

	private:

		Camera* mCamera = nullptr;
	};
}
