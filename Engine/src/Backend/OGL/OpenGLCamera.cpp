#include <Backend/OGL/OpenGLCamera.h>

namespace Engine
{
	OGLCamera::OGLCamera()
		: mView(1), mProjection(1)
	{
	}

	OGLCamera::OGLCamera(glm::vec4 Eye, glm::vec4 At, glm::vec4 Up, float ViewWidth, float ViewHeight, const std::string& Name)
	{
		mEye = Eye;
		mAt = At;
		mUp = Up;
		mName = Name;
		mZDepth = 1;
		mView = glm::mat4(1);
		mProjection = glm::mat4(1);
		mViewWidth = ViewWidth;
		mViewHeight = ViewHeight;
		mNearPlane = 0.1f;
		mFarPlane = 100.0f;
		mMovementSpeed = 100.0f;
		mPrimary = false;
		mStatic = false;
	}

	void OGLCamera::Update(vec2f position, float deltaTime)
	{
		mEye.x = position.x;
		mEye.y = position.y;

		mAt.x = mEye.x;
		mAt.y = mEye.y;

		mView = glm::lookAt(glm::vec3(mEye), glm::vec3(mAt), glm::vec3(mUp));
		mProjection = glm::orthoLH(0.0f, mViewWidth, mViewHeight, 0.0f, -1.0f, 1.0f);
	}

	void OGLCamera::Update(vec2f position)
	{
		mEye.x = position.x;
		mEye.y = position.y;
		
		mAt.x = mEye.x;
		mAt.y = mEye.y;

		mView = glm::lookAt(glm::vec3(mEye), glm::vec3(mAt), glm::vec3(mUp));
		mProjection = glm::orthoLH(0.0f, mViewWidth, mViewHeight, 0.0f, -1.0f, 1.0f);
	}

	void OGLCamera::Update()
	{
		mAt.x = mEye.x;
		mAt.y = mEye.y;

		mView = glm::lookAt(glm::vec3(mEye), glm::vec3(mAt), glm::vec3(mUp));
		mProjection = glm::orthoLH(0.0f, mViewWidth, mViewHeight, 0.0f, -1.0f, 1.0f);
	}


	//void OGLCamera::UpdateMovement(float deltaTime)
	//{
	//	float speed = mMovementSpeed * deltaTime;
	//}

}