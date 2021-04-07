#pragma once
#include <Engine/Layer.h>

// This is the editor interface

class GUILayer : public Engine::Layer
{
public:
	GUILayer();
	virtual ~GUILayer() = default;

	virtual void Render() override;
	virtual void Update() override;
};

