#pragma once
#include <string>

namespace Engine
{
	class Device
	{
	public:
		/*static const std::string& GetAdapter() { return mAdapterName; }

		static int GetMemorySize() { return mMemorySize; }*/

	protected:
		Device* mInstance;

		const std::string mAdapterName;
		int mMemorySize;

	};


}