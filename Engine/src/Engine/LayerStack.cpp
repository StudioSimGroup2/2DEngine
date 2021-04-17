#include "LayerStack.h"
#include <algorithm>

namespace Engine
{
	LayerStack::LayerStack()
	= default;

	LayerStack::~LayerStack()
	{
		for (Layer* l : mLayers)
		{
			delete l;
			l = nullptr;
		}
			
	}

	void LayerStack::AddLayerToStack(Layer* layer)
	{
		mLayers.emplace(mLayers.begin(), layer);
	}

	void LayerStack::RemoveLayerFromStack(Layer* layer)
	{
		auto itr = std::find(mLayers.begin(), mLayers.end(), layer);
		if (itr != mLayers.end())
		{
			mLayers.erase(itr);
		}
	}
}
