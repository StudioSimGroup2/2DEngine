#pragma once
#include "../Component.h"
#include <Engine/Light.h>


namespace Engine
{
	class ENGINE_API LightComp : public Component
	{
	public:
		LightComp();
		~LightComp() override;

		virtual void Init() override;

		virtual void Start() override;

		virtual void Update() override;

		virtual void Render() override;

		virtual void InternalUpdate() override;

		virtual void InternalRender() override;

		void SetRadius(float r) { mLight->radius = r; }
		void SetIntensity(float i) { mLight->intensity = i; }

		int GetType() { return mLight->type; }
		float GetRadius() { return mLight->radius; }
		float GetIntensity() { return mLight->intensity; }

	private:
		Light* mLight;
	};
}


