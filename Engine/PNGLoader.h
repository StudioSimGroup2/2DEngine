#pragma once

#include <wincodec.h>

#pragma comment(lib, "windowscodecs.lib")


class PNGLoader
{
public:
	PNGLoader(wchar_t* fileName);
	~PNGLoader();
};

