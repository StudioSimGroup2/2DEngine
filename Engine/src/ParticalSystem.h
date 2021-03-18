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
	~ParticleProperties() { delete Texture; }

	vec2f Position;		/* Local position of a single partical */
	vec2f Velocity;
	float Lifetime;			/* Measured in Seconds */
	Sprite* Texture;
	bool Alive;
};

enum class Emmitter
{
	Box = 0,
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
	ParticleSystem(D3D11Device* device, const vec2f& position, const ParticleProperties& particle, size_t count, const Emmitter& emmiter = Emmitter::Box);
	ParticleSystem(D3D11Device* device, const vec2f& position, const vec2f& size, const ParticleProperties& particle, size_t count, const Emmitter& emmiter = Emmitter::Box);
	~ParticleSystem();

	void Update(float dt);
	void Render();

	inline void SetPosition(const vec2f& position) { mPosition = position; }
	inline void SetGravity(float gravity) { mGravity = gravity; }
	inline void SetRate(float rate) { mRate = rate; }
	inline void SetSize(const vec2f& size) { mSize = size; }

	inline const vec2f& GetPosition() const { return mPosition; }
	inline float GetGravity() const { return mGravity; }
	inline float GetRate() const { return mRate; }
	inline const vec2f& GetSize() { return mSize; }


private:
	D3D11Device* mDevice;					// Will need openGL device support too...
	vec2f mPosition;						/* Position of the partical emmiter */
	ParticleProperties mParticleProperties;
	vec2f mSize;
	size_t mParticleCount;
	Emmitter mEmmiter;

	float mGravity;
	float mRate;							/* Constant rate of partical emmission */
	float mCurrentRate;						/* Current rate counter */
	std::vector<ParticleProperties*> mParticles;

	void InitParticles(size_t count);
};

