#pragma once

#include "Layer.h"
#include <vector>

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void AddLayerToStack(Layer* layer);
		void RemoveLayerFromStack(Layer* layer);

		std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
		std::vector<Layer*>::iterator end() { return mLayers.end(); }

	private:
		std::vector<Layer*> mLayers;
	};
}

