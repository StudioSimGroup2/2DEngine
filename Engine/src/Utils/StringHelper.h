#pragma once
#include <string>

// String Helper class taken from https://github.com/Pindrought/DirectX-11-Engine-VS2017

class StringHelper
{
public:
	static std::wstring StringToWide(std::string str);
	static std::string GetDirectoryFromPath(const std::string& filepath);
	static std::string GetFileExtension(const std::string& filename);
};