#include "EngineTime.h"

namespace Engine
{
	DeltaTime* DeltaTime::mInstance = nullptr;
	
	DeltaTime* DeltaTime::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new DeltaTime();

		return mInstance;
	}

	void DeltaTime::Shutdown()
	{
		if (mInstance == nullptr)
			return;

		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}

}