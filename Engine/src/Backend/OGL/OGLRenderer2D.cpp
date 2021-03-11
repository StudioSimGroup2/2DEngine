#include "OGLRenderer2D.h"

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <CameraManager.h>

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

		Camera* camera = CameraManager::Get()->GetPrimaryCamera();

		//// Todo:
		//// weird mvp stuff

		//glm::mat4 Model = glm::mat4(1.0f);
		//Model = glm::rotate(Model, 0.0f, glm::vec3(1, 0, 0)) * glm::rotate(Model, 0.0f, glm::vec3(0, 1, 0)) * glm::rotate(Model, 0.0f, glm::vec3(0, 0, 1));
		//Model = glm::scale(Model, glm::vec3(1.0f, 1.0f, 1.0f));
		//Model = glm::translate(Model, glm::vec3(position.x, position.y, 0));
		//glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * Model;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::scale(model, glm::vec3(33.0f, 34.0f, 0.0f)); // fix for sprites rendering at 32x32

		static_cast<OGLShader*>(mShader)->SetMatrix("model", model);
		static_cast<OGLShader*>(mShader)->SetMatrix("projection", camera->GetProjectionMatrix());
		//static_cast<OGLShader*>(mShader)->SetMatrix("View", camera->GetViewMatrix());
		//static_cast<OGLShader*>(mShader)->SetMatrix("World", Model);

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
