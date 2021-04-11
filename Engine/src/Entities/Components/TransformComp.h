#pragma once

#include "../Component.h"
#include <Utils/Math.h> // Swap this class out for GLM math

namespace Engine
{
	class ENGINE_API TransformComp : public Component
	{
	public:
		TransformComp();
		TransformComp(GameObject* parent);

		void SetPosition(float x, float y) { mPosition.x = x; mPosition.y = y; }
		void SetRotation(float x, float y) { mRotation.x = x; mRotation.y = y; }
		void SetScale(float x, float y) { mScale.x = x; mScale.y = y; }

		void Update() override;
		void Render() override;

		vec2f GetPosition() const { return mPosition; }
		vec2f GetRotation() const { return mRotation; }
		vec2f GetScale() const { return mScale; }

	private:
		void Init();

		vec2f mPosition;
		vec2f mRotation;
		vec2f mScale;
	};
}

