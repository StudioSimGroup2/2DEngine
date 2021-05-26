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

		float GetParticleCount() { return mParticleSystem->GetParticleCount(); }
		float& GetRate() { return mParticleSystem->GetRate(); }
		float& GetGravity() { return mParticleSystem->GetGravity(); }
		float GetLifetime() const { return mParticleSystem->GetLifetime(); }
		vec2f& GetVelocity() { return mParticleSystem->GetVelocity(); }
		Texture* GetTexture() { return mParticleSystem->GetTexture(); }
		Emmitter& GetEmmiter() { return mParticleSystem->GetEmmiter(); }



		void SetRate(float rate) { mParticleSystem->SetRate(rate); }
		void SetGravity(float ammount) { mParticleSystem->SetGravity(ammount); }


		//void ShowEmmiterIcon(bool flag) { mShowEmmiterIcon = flag; }


	private:
		void Init();

		ParticleSystem* mParticleSystem;
	};
}
