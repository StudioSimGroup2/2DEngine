#pragma once

// Based on Developing an Open-Source Lightweight GameEngine with DNN Support by Haechan Parkand and Nakhoon Baek
// https://www.mdpi.com/2079-9292/9/9/1421/htm

#include "Engine/Core.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Render() {}
		virtual void Update() {}
	};
}



