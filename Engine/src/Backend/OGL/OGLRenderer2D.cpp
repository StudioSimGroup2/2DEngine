#include "OGLRenderer2D.h"
#include <CameraManager.h>

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "OpenGLCamera.h"

namespace Engine
{
	OGLRenderer2D::OGLRenderer2D(Shader* shader)
	{
		mShader = shader;

		InitBuffers();
	}

	void OGLRenderer2D::Draw(vec2f& position, vec2f& rotation, vec2f& scale, Texture* textureToRender)
	{
		mShader->Load();

		Camera* camera = CameraManager::Get()->GetPrimaryCamera();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(rotation.x, rotation.y, 1.0f));

		model = glm::scale(model, glm::vec3(32.0f * scale.x, 32.0f * scale.y, 0.0f)); // fix for sprites rendering at 32x32

		dynamic_cast<OGLShader*>(mShader)->SetMatrix("model", model);
		dynamic_cast<OGLShader*>(mShader)->SetMatrix("projection", camera->GetProjectionMatrix());
		dynamic_cast<OGLShader*>(mShader)->SetBool("flipX", mFlipX);
		dynamic_cast<OGLShader*>(mShader)->SetBool("flipY", mFlipY);
		dynamic_cast<OGLShader*>(mShader)->SetVector4("Colour", glm::vec4(mColour[0], mColour[1], mColour[2], mColour[3]));

		glActiveTexture(GL_TEXTURE0);
		textureToRender->Load();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void OGLRenderer2D::InitBuffers()
	{
		// configure VAO/VBO
		unsigned int VBO;
		float vertices[] = {
			// pos      // tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

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
