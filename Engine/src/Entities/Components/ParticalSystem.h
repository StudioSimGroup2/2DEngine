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

#include "../Component.h"
#include <Utils/Texture.h>
#include "Entities/Components/ParticleComp.h"

namespace Engine
{

	enum class Emmitter
	{
		Square = 0,
		Circle,
		Cone
	};

	class ENGINE_API ParticleSystem : public Component
	{
	public:
		//ParticleSystem();
		//ParticleSystem(const vec2f& emmitterPos, size_t count, const Emmitter& emmiter = Emmitter::Square);
		//ParticleSystem(const vec2f& emmitterPos, size_t count, const Emmitter& emmiter = Emmitter::Square);
		//~ParticleSystem() override;

		void Update() override;
		void Render() override;

		void SetPosition(const vec2f& position) { mPosition = position; }
		void SetGravity(float gravity) { mGravity = gravity; }
		void SetRate(float rate) { mRate = rate; }
		void SetSize(const vec2f& size) { mSize = size; }
		void SetLifetime(const float lifetime) { mParticleProperties.Lifetime = lifetime; }

		vec2f& GetPosition() { return mPosition; }
		vec2f& GetSize() { return mSize; }
		float& GetRate() { return mRate; }
		float& GetGravity() { return mGravity; }
		float& GetLifetime() { return mParticleProperties.Lifetime; }
		vec2f& GetVelocity() { return mParticleProperties.Velocity; }
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