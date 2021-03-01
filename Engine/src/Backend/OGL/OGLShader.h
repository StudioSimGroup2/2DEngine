#pragma once

#include "Utils/Shader.h"
#include "Glad/glad.h"

#include <GLM/glm.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

namespace Engine
{
	class OGLShader : public Shader
	{
	public:
		OGLShader(const std::string& name, const std::string& path);
		~OGLShader();

		virtual void Load() const override;
		virtual void Unload() const override;

		void SetInt(const std::string& name, int value);
		void SetVector3(const std::string& name, const glm::vec3& value);
		void SetMatrix(const std::string& name, const glm::mat4& matrix);

		virtual const std::string& GetName() const override { return mName; }

	private:
		bool CompileShaderFromFile(const std::string& path, bool isVertex, int blob);

		unsigned int mID;
	};
}