#pragma once

#include "CameraManager.h"
#include "Utils/AssetManager.h"
#include <Utils/Math.h>
#include <Engine/Renderer/Renderer2D.h>

using namespace Engine;

class Sprite
{
public:
	Sprite(Device* dev, const std::string& name, const std::string& path, vec2f position);
	~Sprite();

	void AddRendererComponent(Renderer2D* renderer);
	void Update(float deltaTime);
	void Draw();

private:
	std::string mName;
	vec2f mPosition;

	Texture2D* mSprTexture = nullptr;
	Renderer2D* mRenderer = nullptr;

	AssetManager* mAssetManager;

	int mScreenWidth, mScreenHeight;
	int mWidth, mHeight;
	float mPosX, mPosY;
	int mPreviousPosX = 0, mPreviousPosY = 0;
};

