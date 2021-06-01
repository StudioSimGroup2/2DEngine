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
		~TransformComp() override;

		void SetPosition(vec2f& pos) { mPosition = pos; }
		void SetRotation(vec2f& rot) { mRotation = rot; }
		void SetScale(vec2f& scale) { mScale = scale; }

		virtual void Init() override;
		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

		void Update() override;
		void Render() override;

		vec2f& GetPosition() { return mPosition; }
		vec2f& GetRotation() { return mRotation; }
		vec2f& GetScale() { return mScale; }

	private:
		vec2f mPosition;
		vec2f mRotation;
		vec2f mScale;
	};
}

