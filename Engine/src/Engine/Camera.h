#pragma once

#include <Utils/Math.h>
#include <GLM/ext/vector_float4.hpp>
#include <string>
#include <GLM/ext/matrix_float4x4.hpp>

#include <DirectXMath.h>

namespace Engine
{
	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual void Update(vec2f position, float deltaTime) = 0;
		virtual void Update(vec2f position) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Update() = 0;

		void Lerp(const vec2f from, const vec2f to, float t);
		void SetPrimary(bool option) { mPrimary = option; }
		void SetEditorCamera(bool option) { mEditorCamera = option; }
		void SetName(const std::string& name) { mName = name; }

		float Lerpf(float a, float b, float t);

		vec2f Lerp2f(vec2f a, vec2f b, float t);

		const bool GetIsPrimary() const { return mPrimary; }
		const bool GetIsEditorCamera() const { return mEditorCamera; }
		const std::string& GetName() { return mName; }

		DirectX::XMMATRIX GetProjectionMatrix() { return mProjection; }
		DirectX::XMMATRIX GetViewMatrix() { return mView; }

		void SetFOV(float fov) {}
		void SetNear(float cNear) { mNearPlane = cNear; }
		void SetFar(float cFar) { mFarPlane = cFar; }

		float GetFOV() { return 0.0f; }
		float GetNear() { return mNearPlane; }
		float GetFar() { return mFarPlane; }
		
	protected:
		DirectX::XMMATRIX mView, mProjection;

		glm::vec4 mEye, mAt, mUp;
		std::string mName;
		float mZDepth;
		float mViewWidth, mViewHeight;
		float mNearPlane, mFarPlane;
		float mMovementSpeed;
		bool mPrimary;			// Is this the active camera
		bool mStatic;			// Can the camera move? 
		bool mEditorCamera;
	};


}
