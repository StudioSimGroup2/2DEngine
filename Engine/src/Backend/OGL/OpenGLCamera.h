#pragma once
//#include "Engine/Defines.h"
#include "..\..\Camera.h"
#include <GLM/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class OGLCamera : public Camera
{
public:

	OGLCamera();
	OGLCamera(glm::vec4 Eye, glm::vec4 At = glm::vec4(0, 0, 0, 1), glm::vec4 Up = glm::vec4(0, 1, 0, 1), float ViewWidth = 1280, float ViewHeight = 720, const std::string& Name = "-New Camera-");

	void Update(float deltaTime) override;  // Updates the view and projection matrices

	const glm::mat4 GetViewMatrix() const override { return mView; }
	const glm::mat4 GetProjectionMatrix() const override { return mProjection; }

private:
	glm::mat4 mView, mProjection;

	void UpdateMovement(float deltaTime) override;


};