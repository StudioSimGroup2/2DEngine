#pragma once

namespace Engine
{
	class DeltaTime
	{
	public:
		static DeltaTime* GetInstance();
		float GetDeltaTime() { return deltaTime; };
		void SetDeltaTime(float newDelta) { deltaTime = newDelta; };

		static void Shutdown();

	private:
		DeltaTime() {};
		static DeltaTime* mInstance;
		float deltaTime = 0;
	};

}
