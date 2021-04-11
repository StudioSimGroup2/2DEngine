#pragma once

#include "Engine/Core.h"

class PoolAllocator;

namespace Engine
{
	class ENGINE_API MemoryManager
	{
	public:
		static void GetInstance();
		void Shutdown();

	private:
		MemoryManager();

		static MemoryManager* mInstance;
	};

}
