#pragma once
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Utils/Math.h>
#include <Utils\AssetManager.h>
#include <Backend\D3D11\D3D11Device.h>
#include <Backend\D3D11\D3D11Renderer2D.h>

#include "Sprite.h"

struct ParticleProperties
{
	ParticleProperties() = default;
	ParticleProperties(vec2f velocity, float lifetime, Sprite* texture)
		: Velocity(velocity), Lifetime(lifetime), Texture(texture), Alive(false) {}

	vec2f Position;		/* Local position of a single partical */
	vec2f Velocity;
	float Lifetime;		/* Measured in Seconds */
	Sprite* Texture;
	bool Alive;
};

enum class Emmitter
{
	Square = 0,
	Circle,
	Cone
};

// In-built textures for particles (Currently not used)
enum class ParticleStyle
{
	Custom = 0,
	Circle,
	Square,
	Triangle
};


class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(D3D11Device* device, const vec2f& emmitterPos, const ParticleProperties& particle, size_t count, const Emmitter& emmiter = Emmitter::Square);
	ParticleSystem(D3D11Device* device, const vec2f& emmitterPos, const vec2f& emmitterSize, const ParticleProperties& particle, size_t count, const Emmitter& emmiter = Emmitter::Square);
	~ParticleSystem();

	void Update(float dt);
	void Render();

	void SetPosition(const vec2f& position) { mPosition = position; }
	void SetGravity(float gravity) { mGravity = gravity; }
	void SetRate(float rate) { mRate = rate; }
	void SetSize(const vec2f& size) { mSize = size; }

	vec2f& GetPosition() { return mPosition; }
	vec2f& GetSize() { return mSize; }
	float& GetRate() { return mRate; }
	float& GetGravity() { return mGravity; }
	float& GetLifetime() { return mParticleProperties.Lifetime; }
	vec2f& GetVelocity() { return mParticleProperties.Velocity; }
	Emmitter& GetEmmiter() { return mEmmiter; }
	void ShowEmmiterIcon(bool flag) { mShowEmmiterIcon = flag; }

private:
	D3D11Device* mDevice;					/* Will need openGL device support too...*/
	vec2f mPosition;						/* Position of the partical emmiter */
	ParticleProperties mParticleProperties;
	vec2f mSize;
	size_t mParticleCount;
	Emmitter mEmmiter;
	Sprite* mEmmiterIcon;

	float mGravity;
	float mRate;							/* Constant rate of partical emmission */
	float mCurrentRate;						/* Current rate counter */
	std::vector<ParticleProperties*> mParticles;
	bool mShowEmmiterIcon;

	void InitParticles(size_t count);
};

