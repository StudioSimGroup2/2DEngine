#pragma once

#include "Engine/Renderer/Renderer2D.h"
#include <Backend/OGL/OGLShader.h>

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

namespace Engine
{
	class OGLRenderer2D : public Renderer2D
	{
	public:
		OGLRenderer2D(OGLShader* shader);

		virtual void Draw(vec2f position, Texture* textureToRender) const override;

	private:
		void InitBuffers();

		unsigned int mVAO;

		struct ConstantBuffer
		{
			glm::mat4 mWorld;
			glm::mat4 mView;
			glm::mat4 mProjection;
		};

		struct VertexType
		{
			glm::vec3 position;
			glm::vec2 texture;
		};
	};
}

