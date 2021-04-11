#include "MemoryManager.h"
#include <iostream>

#include "Utils/Logger.h"

namespace Engine
{
	MemoryManager* MemoryManager::mInstance = nullptr;

	void MemoryManager::GetInstance()
	{
		if (mInstance == nullptr)
			mInstance = new MemoryManager();
	}

	void MemoryManager::Shutdown()
	{
		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}

	MemoryManager::MemoryManager()
	{
		Logger::Init(GetStdHandle(STD_OUTPUT_HANDLE)); // Get handle to console (for text coloring)
		Logger::SetLogLevel(LogStates::LOG_ERR | LogStates::LOG_WARN | LogStates::LOG_MSG);

		Logger::LogMsg("Logger initalised!", __FILE__);

		Logger::LogMsg("Memory Manager Initialised!");
	}
}
