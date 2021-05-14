#pragma once

#include <Entities/GameObject.h>

using namespace Engine;

class Player : public Engine::GameObject
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void OnEnable() override;
	virtual void Render() override;
	virtual void OnDisable() override;
};

