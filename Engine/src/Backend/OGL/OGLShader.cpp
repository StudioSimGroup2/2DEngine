#include "OGLShader.h"

#include <fstream>
#include <iterator>
#include <iostream>

#define GL_PIXEL_SHADER GL_FRAGMENT_SHADER

namespace Engine
{
	OGLShader::OGLShader(const std::string& name, const std::string& path)
	{
		mName = name;

		bool result = true;
		unsigned int blobVS;
		unsigned int blobPS;

		blobVS = glCreateShader(GL_VERTEX_SHADER);
		blobPS = glCreateShader(GL_PIXEL_SHADER);

		result = CompileShaderFromFile(path, true, blobVS);

		result = CompileShaderFromFile(path, false, blobPS);

		mID = glCreateProgram();
		glAttachShader(mID, blobVS);
		glAttachShader(mID, blobPS);
		glLinkProgram(mID);

		int success;
		char infoLog[512];

		glGetProgramiv(mID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(mID, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}

		glDeleteShader(blobVS);
		glDeleteShader(blobPS);
	}

	OGLShader::~OGLShader()
	{
	}

	void OGLShader::Load() const
	{
		glUseProgram(mID);
	}

	void OGLShader::Unload() const
	{
		//glUseProgram(0);
	}

	bool OGLShader::CompileShaderFromFile(const std::string& path, bool isVertex, int blob)
	{
		std::ifstream ifs(path.c_str(), std::ios::in);

		if (!ifs.is_open())
			return false;

		std::string data;
		data.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

		ifs.close();

		std::string contents;

		if (isVertex)
		{
			contents = "#version 460 core\n#define VERTEX_SHADER\n" + data;
		}
		else
		{
			contents = "#version 460 core\n#define PIXEL_SHADER\n" + data;
		}

		const GLchar* source = contents.c_str();

		glShaderSource(blob, 1, &source, NULL);
		glCompileShader(blob);

		int success;
		char infoLog[512];

		glGetShaderiv(blob, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(blob, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;

			return false;
		}

		//TODO:
		// Error Checking

		return true;
	}
}

