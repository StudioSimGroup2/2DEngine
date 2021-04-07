#pragma once

#include "CameraManager.h"
#include "Utils/AssetManager.h"
#include <Utils/Math.h>
#include <Engine/Renderer/Renderer2D.h>

using namespace Engine;

class ENGINE_API Sprite
{
public:
	Sprite(char* name, vec2f* position, Texture* tex = nullptr, char* texName = '\0', char* texPath = '\0');
	~Sprite();

	virtual void AddRendererComponent(Renderer2D* renderer);
	void Update(float deltaTime);
	void Draw();

	void SetPosition(vec2f* newPosition) { mPosition = newPosition; }
	const vec2f* GetPosition() const { return mPosition; }
	std::string GetName() { return mName; };

private:
	std::string mName;
	vec2f* mPosition;

	Texture* mSprTexture = nullptr;
	Renderer2D* mRenderer = nullptr;

	int mWidth, mHeight;
};