#pragma once

#include "Utils/Shader.h"
#include "Glad/glad.h"

namespace Engine
{
	class OGLShader : public Shader
	{
	public:
		OGLShader(const std::string& name, const std::string& path);
		~OGLShader();

		virtual void Load() const override;
		virtual void Unload() const override;

		virtual const std::string& GetName() const override { return mName; }

	private:
		bool CompileShaderFromFile(const std::string& path, bool isVertex, int blob);

		unsigned int mID;
	};
}