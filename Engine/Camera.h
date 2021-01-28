#pragma once
// TODO: REALLY move to a PCH later...
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>
using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(XMFLOAT4 Eye, XMFLOAT4 At = XMFLOAT4(0,0,0,1), XMFLOAT4 Up = XMFLOAT4(0, 1, 0, 1));
	~Camera() = default;

	void Update(); // Updates the view and projection matrices

	inline const XMFLOAT4 GetEye() const { return mEye; }
	inline const XMFLOAT4 GetAt() const { return mAt; }
	inline const XMFLOAT4 GetUp() const { return mUp; }
	inline const XMMATRIX GetViewMatrix() const { return mView; }
	inline const XMMATRIX GetProjectionMatrix() const { return mProjection; }

	inline void SetEye(XMFLOAT4 Eye) { mEye = Eye; }
	inline void SetAt(XMFLOAT4 At) { mAt = At; }
	inline void SetUp(XMFLOAT4 Up) { mUp = Up; }

private:
	XMFLOAT4 mEye, mAt, mUp;
	XMMATRIX mView, mProjection;
};
