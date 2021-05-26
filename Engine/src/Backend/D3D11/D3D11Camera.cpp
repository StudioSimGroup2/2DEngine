#include <Backend/D3D11/D3D11Camera.h>
namespace Engine
{
	D3DCamera::D3DCamera(XMFLOAT4 Eye, XMFLOAT4 At, XMFLOAT4 Up, float ViewWidth, float ViewHeight, const std::string& Name, bool editor)
	{
		mEye = ToGLM(Eye);
		mAt = ToGLM(At);
		mUp = ToGLM(Up);
		mName = Name;
		mZDepth = 1;
		mView = XMMatrixIdentity();
		mProjection = XMMatrixIdentity();
		mViewWidth = ViewWidth;
		mViewHeight = ViewHeight;
		mNearPlane = 0.1f;
		mFarPlane = 100.0f;
		mMovementSpeed = 100.0f;
		mPrimary = false;
		mStatic = false;
		mEditorCamera = editor;
	}

	D3DCamera::D3DCamera(glm::vec4 Eye, glm::vec4 At, glm::vec4 Up, float ViewWidth, float ViewHeight, const std::string& Name, bool editor)
	{
		mEye = Eye;
		mAt = At;
		mUp = Up;
		mName = Name;
		mZDepth = 1;
		mView = XMMatrixIdentity();
		mProjection = XMMatrixIdentity();
		mViewWidth = ViewWidth;
		mViewHeight = ViewHeight;
		mNearPlane = 0.1f;
		mFarPlane = 100.0f;
		mMovementSpeed = 100.0f;
		mPrimary = false;
		mStatic = false;
		mEditorCamera = editor;
	}

	void D3DCamera::Update(vec2f position)
	{
		mEye.x = position.x;
		mEye.y = position.y;

		// Force the cameras at to be where the eye is, otherwise we get some weird skewing.
		mAt.x = mEye.x;
		mAt.y = mEye.y;
		if (mZDepth < 0.0f)	// Cameras shouldn't have a negitive z-depth. It will result in the scene being fliped!
			mZDepth = 0.0f;

		mEye.z = -mZDepth; // Flip the z-depth, Higher Z-depth = object will render infront of others!
		mAt.z = 0.001f;

		XMVECTOR Eye = XMLoadFloat4(&ToXM(mEye));
		XMVECTOR At = XMLoadFloat4(&ToXM(mAt));
		XMVECTOR Up = XMLoadFloat4(&ToXM(mUp));

		mView = XMMatrixLookAtLH(Eye, At, Up);
		mProjection = XMMatrixOrthographicLH(mViewWidth, mViewHeight, mNearPlane, mFarPlane); // Need to tweek the quads verts to use this version
	}

	void D3DCamera::Update()
	{
		// Force the cameras at to be where the eye is, otherwise we get some weird skewing.
		mAt.x = mEye.x;
		mAt.y = mEye.y;
		if (mZDepth < 0.0f)	// Cameras shouldn't have a negitive z-depth. It will result in the scene being fliped!
			mZDepth = 0.0f;

		mEye.z = -mZDepth; // Flip the z-depth, Higher Z-depth = object will render infront of others!
		mAt.z = 0.001f;

		XMVECTOR Eye = XMLoadFloat4(&ToXM(mEye));
		XMVECTOR At = XMLoadFloat4(&ToXM(mAt));
		XMVECTOR Up = XMLoadFloat4(&ToXM(mUp));

		mView = XMMatrixLookAtLH(Eye, At, Up);
		mProjection = XMMatrixOrthographicLH(mViewWidth, mViewHeight, mNearPlane, mFarPlane); // Need to tweek the quads verts to use this version
	}

	void D3DCamera::Update(float deltaTime)
	{
		// Force the cameras at to be where the eye is, otherwise we get some weird skewing.
		mAt.x = mEye.x;
		mAt.y = mEye.y;
		if (mZDepth < 0.0f)	// Cameras shouldn't have a negitive z-depth. It will result in the scene being fliped!
			mZDepth = 0.0f;

		mEye.z = -mZDepth; // Flip the z-depth, Higher Z-depth = object will render infront of others!
		mAt.z = 0.001f;

		XMVECTOR Eye = XMLoadFloat4(&ToXM(mEye));
		XMVECTOR At = XMLoadFloat4(&ToXM(mAt));
		XMVECTOR Up = XMLoadFloat4(&ToXM(mUp));

		mView = XMMatrixLookAtLH(Eye, At, Up);
		mProjection = XMMatrixOrthographicLH(mViewWidth, mViewHeight, mNearPlane, mFarPlane); // Need to tweek the quads verts to use this version
	}


	void D3DCamera::Update(vec2f pos, float deltaTime)
	{
		mEye.x = pos.x;
		mEye.y = pos.y;

		// Force the cameras at to be where the eye is, otherwise we get some weird skewing.
		mAt.x = mEye.x;
		mAt.y = mEye.y;
		if (mZDepth < 0.0f)	// Cameras shouldn't have a negitive z-depth. It will result in the scene being fliped!
			mZDepth = 0.0f;

		mEye.z = -mZDepth; // Flip the z-depth, Higher Z-depth = object will render infront of others!
		mAt.z = 0.001f;

		XMVECTOR Eye = XMLoadFloat4(&ToXM(mEye));
		XMVECTOR At = XMLoadFloat4(&ToXM(mAt));
		XMVECTOR Up = XMLoadFloat4(&ToXM(mUp));

		mView = XMMatrixLookAtLH(Eye, At, Up);
		mProjection = XMMatrixOrthographicLH(mViewWidth, mViewHeight, mNearPlane, mFarPlane); // Need to tweek the quads verts to use this version
	}

	//void D3DCamera::UpdateMovement(float deltaTime)
	//{
	//	float speed = mMovementSpeed * deltaTime;
	//	if (GetAsyncKeyState(0x57)) // W key
	//	{
	//		mEye.y += speed;
	//	}
	//	if (GetAsyncKeyState(0x53)) // S key
	//	{
	//		mEye.y -= speed;
	//	}
	//	if (GetAsyncKeyState(0x41)) // A key
	//	{
	//		mEye.x -= speed;
	//	}
	//	if (GetAsyncKeyState(0x44)) // D key
	//	{
	//		mEye.x += speed;
	//	}
	//}
}
