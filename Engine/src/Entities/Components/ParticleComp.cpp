#include "ParticleComp.h"
#include "..\GameObject.h"

namespace Engine {

	ParticleComp::ParticleComp() : Component()
	{
		
	}

	ParticleComp::~ParticleComp()
	{
		mParent = nullptr;
		delete mParticleSystem;
	}


	void ParticleComp::Init()
	{

		// TODO: Loading in values is pointless as INIT overrides them...
		// Saving is a-ok, just loading needs re-working atm
		// We want to support default values incase youre just making a default particle system to be saved later

		mType = TYPE::COMPONENT_PARTICLE;

		vec2f emmitterPos = mParent->GetComponent<TransformComp>()->GetPosition();
		vec2f particleScale = mParent->GetComponent<TransformComp>()->GetScale();

		// Default values
		Particle layout;
		layout.Lifetime = 3;
		layout.Alive = false;
		layout.Velocity = vec2f(0, -200);
		layout.Style = ParticleTexture::Circle;
		layout.Scale = particleScale;
		layout.TexturePath = "Assets\\Textures\\Mario.png";

		mParticleSystem = new ParticleSystem(emmitterPos, layout, 150);
		mParticleSystem->SetRate(0.1);
		mParticleSystem->SetGravity(140.0f);
	}

	void ParticleComp::Start()
	{
	}

	void ParticleComp::InternalUpdate()
	{
		vec2f emmitterPos = mParent->GetComponent<TransformComp>()->GetPosition();
		vec2f particleScale = mParent->GetComponent<TransformComp>()->GetScale();

		mParticleSystem->SetPosition(emmitterPos);
		mParticleSystem->SetParticleScale(particleScale);

		mParticleSystem->Update();
	}

	void ParticleComp::InternalRender()
	{
	}

	void ParticleComp::Update()
	{

	}

	void ParticleComp::Render()
	{
		mParticleSystem->Render();
	}



}
