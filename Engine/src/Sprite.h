#pragma once

#include "CameraManager.h"
#include "Utils/AssetManager.h"
#include <Utils/Math.h>
#include <Engine/Renderer/Renderer2D.h>

using namespace Engine;

//todo: turn this in to a virtual class, 

class Sprite
{
public:
	Sprite(Device* dev, const std::string& name, const std::string& path, vec2f position);
	~Sprite();

	void AddRendererComponent(Renderer2D* renderer);
	void Update(float deltaTime);
	void Draw();

	void SetPosition(vec2f newPosition) { mPosition = newPosition; }
	const vec2f& GetPosition() const { return mPosition; }

private:
	std::string mName;
	vec2f mPosition;

	Texture* mSprTexture = nullptr;
	Renderer2D* mRenderer = nullptr;

	AssetManager* mAssetManager;

	int mScreenWidth, mScreenHeight;
	int mWidth, mHeight;
	float mPosX, mPosY;
	int mPreviousPosX = 0, mPreviousPosY = 0;
};

