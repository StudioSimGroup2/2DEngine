#pragma once

#include "Engine/Defines.h"

#if GRAPHICS_LIBRARY == 0 //DX11
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Utils/Math.h>

#include <Engine/Renderer/Device.h>
#include <Engine/Renderer/Renderer2D.h>

#include <Utils/Texture.h>

namespace Engine
{
	enum class ParticleTexture
	{
		Custom = 0,
		Circle,
		Square,
		Triangle
	};

	struct Particle
	{
		//Particle();
		//~Particle();


		vec2f Position;		/* Local position of a single partical */
		vec2f Scale;
		vec2f Velocity;
		float Lifetime;		/* Measured in Seconds */
		const char* TexturePath;
		bool Alive;
		ParticleTexture Style;
		Texture* Texture;
	};

	enum class Emmitter
	{
		Square = 0,
		Circle,
		Cone
	};

	class ParticleSystem
	{
	public:
		ParticleSystem();
		ParticleSystem(const vec2f& emmitterPos, const Particle& particle, size_t count, const Emmitter& emmiter = Emmitter::Square);
		ParticleSystem(const vec2f& emmitterPos, const vec2f& emmitterSize, const Particle& particle, size_t count, const Emmitter& emmiter = Emmitter::Square);
		~ParticleSystem();

		void Update();
		void Render();

		void SetPosition(const vec2f& position) { mPosition = position; }
		void SetParticleScale(const vec2f& scale) { mParticleProperties.Scale = scale; }
		void SetGravity(float gravity) { mGravity = gravity; }
		void SetRate(float rate) { mRate = rate; }
		void SetSize(const vec2f& size) { mSize = size; }
		void SetLifetime(float lifetime) { mParticleProperties.Lifetime = lifetime; }
		void SetVelocity(vec2f velocity) { mParticleProperties.Velocity = velocity; }

		float GetParticleCount() { return mParticleCount; }
		vec2f& GetPosition() { return mPosition; }
		vec2f& GetScale() { return mParticleProperties.Scale; }
		vec2f& GetSize() { return mSize; }
		float& GetRate() { return mRate; }
		float& GetGravity() { return mGravity; }
		float& GetLifetime() { return mParticleProperties.Lifetime; }
		vec2f& GetVelocity() { return mParticleProperties.Velocity; }
		Texture* GetTexture() { return mParticleProperties.Texture; }
		Emmitter& GetEmmiter() { return mEmmiter; }
		void ShowEmmiterIcon(bool flag) { mShowEmmiterIcon = flag; }

	private:
		void Init();

		Renderer2D* mRenderer = nullptr;		/* Will need openGL device support too...*/
		vec2f mPosition;						/* Position of the partical emmiter */
		Particle mParticleProperties;
		vec2f mSize;
		size_t mParticleCount;
		Emmitter mEmmiter;
		Texture* mEmmiterIcon; //?? not sure how to hanle this 

		float mGravity;
		float mRate;							/* Constant rate of partical emmission */
		float mCurrentRate;						/* Current rate counter */
		std::vector<Particle*> mParticles;
		bool mShowEmmiterIcon;

		void InitParticles(size_t count);
		void SetupTexture(Particle* particle);
	};
}
#elif GRAPHICS_LIBRARY == 1 // OpenGL


#endif