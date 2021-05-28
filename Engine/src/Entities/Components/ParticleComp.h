#pragma once

#include "../Component.h"
#include "ParticalSystem.h"	// TODO: Move into the src folder when done

namespace Engine
{
	class ENGINE_API ParticleComp : public Component
	{
	public:
		ParticleComp();
		ParticleComp(GameObject* parent);
		~ParticleComp() override;


		virtual void Start() override;
		virtual void InternalUpdate() override;
		virtual void InternalRender() override;

		void Update() override;
		void Render() override;

		int GetParticleCount() { return mParticleSystem->GetParticleCount(); }
		float& GetRate() { return mParticleSystem->GetRate(); }
		float& GetGravity() { return mParticleSystem->GetGravity(); }
		float GetLifetime() const { return mParticleSystem->GetLifetime(); }
		vec2f& GetVelocity() { return mParticleSystem->GetVelocity(); }
		Texture* GetTexture() { return mParticleSystem->GetTexture(); }
		Emmitter& GetEmmiter() { return mParticleSystem->GetEmmiter(); }
		const glm::vec4& GetColour() const { return mParticleSystem->GetColour(); }
		const Emmitter GetEmmitter() const { return mParticleSystem->GetEmmiter(); }
		const ParticleTexture GetParticleTexture() const { return mParticleSystem->GetParticleTex(); }


		void SetRate(float rate) { mParticleSystem->SetRate(rate); }
		void SetGravity(float ammount) { mParticleSystem->SetGravity(ammount); }
		void SetLifetime(float lifetime) { mParticleSystem->SetLifetime(lifetime); }
		void SetVelocity(vec2f velocity) { mParticleSystem->SetVelocity(velocity); }
		void SetColour(glm::vec4 colour) { mParticleSystem->SetColour(colour); }
		void SetEmmitter(Emmitter style) { mParticleSystem->SetEmmitter(style); }
		void SetParticleTex(ParticleTexture style) { mParticleSystem->SetParticleTex(style); }
		void SetParticleCount(int newSize) { mParticleSystem->SetParticleCount(newSize); }
		//void ShowEmmiterIcon(bool flag) { mShowEmmiterIcon = flag; }


	private:
		void Init();

		ParticleSystem* mParticleSystem;
	};
}
