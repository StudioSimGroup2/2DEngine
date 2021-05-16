#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>

#include "..\..\Camera.h"
#include "Engine/Defines.h"

using namespace DirectX;


class D3DCamera : public Camera
{
public:
	D3DCamera();
	D3DCamera(XMFLOAT4 Eye, XMFLOAT4 At = XMFLOAT4(0, 0, 0, 1), XMFLOAT4 Up = XMFLOAT4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight = 720, const std::string& Name = "-New Camera-");
	D3DCamera(glm::vec4 Eye, glm::vec4 At = glm::vec4(0, 0, 0, 1), glm::vec4 Up = glm::vec4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight = 720, const std::string& Name="-New Camera-");
	~D3DCamera() = default;

	void Update(float deltaTime) override;  // Updates the view and projection matrices

	const XMMATRIX GetViewMatrix() const override { return mView; }
	const XMMATRIX GetProjectionMatrix() const override { return mProjection; }

private:
	XMMATRIX mView, mProjection;

	void UpdateMovement(float deltaTime) override;

	inline glm::vec4 ToGLM(XMFLOAT4 xmFloat4) const { return glm::vec4(xmFloat4.x, xmFloat4.y, xmFloat4.z, xmFloat4.w); }
	inline XMFLOAT4 ToXM(glm::vec4 vec4) const { return XMFLOAT4(vec4.x, vec4.y, vec4.z, vec4.w); }
};