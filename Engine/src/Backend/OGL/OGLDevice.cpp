#include "OGLDevice.h"

namespace Engine
{
	OGLDevice* OGLDevice::mInstance = nullptr;
	
	OGLDevice* OGLDevice::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new OGLDevice();

		return mInstance;
	}

	void OGLDevice::ShutdownDevice()
	{
		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
}
