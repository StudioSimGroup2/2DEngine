#include "OGLRenderer2D.h"

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

namespace Engine
{
	OGLRenderer2D::OGLRenderer2D(OGLShader* shader)
	{
		mShader = static_cast<Shader*>(shader);

		InitBuffers();
	}

	void OGLRenderer2D::Draw(vec2f position, Texture* textureToRender) const
	{
		mShader->Load();

		// Todo:
		// weird mvp stuff

		ConstantBuffer cb;
		cb.mProjection = glm::mat4(1.0f);
		cb.mView = glm::mat4(1.0f);
		cb.mWorld = glm::mat4(1.0f);

		static_cast<OGLShader*>(mShader)->SetMatrix("Projection", cb.mProjection);
		static_cast<OGLShader*>(mShader)->SetMatrix("View", cb.mView);
		static_cast<OGLShader*>(mShader)->SetMatrix("World", cb.mWorld);

		glActiveTexture(GL_TEXTURE0);
		textureToRender->Load();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void OGLRenderer2D::InitBuffers()
	{
		unsigned int VBO;
		VertexType vertices[6];
		float left, right, top, bottom;

		// Calculate the screen coordinates of the left side of the bitmap.
		left = (float)((1280 / 2) * -1); // 0 = X position

		// Calculate the screen coordinates of the right side of the bitmap.
		right = left + (float)32;

		// Calculate the screen coordinates of the top of the bitmap.
		top = (float)(720 / 2); // 0 = Y position

		// Calculate the screen coordinates of the bottom of the bitmap.
		bottom = top - (float)32;

		vertices[0].position = glm::vec3(left, top, 0.0f);
		vertices[0].texture = glm::vec2(0.0f, 0.0f);

		vertices[1].position = glm::vec3(left, bottom, 0.0f);
		vertices[1].texture = glm::vec2(0.0f, 1.0f);

		vertices[2].position = glm::vec3(right, bottom, 0.0f);
		vertices[2].texture = glm::vec2(1.0f, 1.0f);

		vertices[3].position = glm::vec3(left, top, 0.0f);
		vertices[3].texture = glm::vec2(0.0f, 0.0f);

		vertices[4].position = glm::vec3(right, top, 0.0f);
		vertices[4].texture = glm::vec2(1.0f, 0.0f);

		vertices[5].position = glm::vec3(right, bottom, 0.0f);
		vertices[5].texture = glm::vec2(1.0f, 1.0f);

		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(mVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		static_cast<OGLShader*>(mShader)->SetInt("Image", 0);
	}
}
