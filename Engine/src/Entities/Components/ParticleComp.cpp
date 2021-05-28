#include "ParticleComp.h"
#include "..\GameObject.h"

namespace Engine {

	ParticleComp::ParticleComp() : Component()
	{
		Init();
	}

	ParticleComp::ParticleComp(GameObject* parent) : Component(parent)
	{
		Init();
	}

	ParticleComp::~ParticleComp()
	{
		mParent = nullptr;
		delete mParticleSystem;
	}


	void ParticleComp::Init()
	{
		mType = TYPE::COMPONENT_PARTICLE;
		

		vec2f emmitterPos = mParent->GetComponent<TransformComp>()->GetPosition();
		vec2f particleScale = mParent->GetComponent<TransformComp>()->GetScale();

		// Default values
		Particle layout;
		layout.Lifetime = 30; 
		layout.Alive = false;
		layout.Velocity = vec2f(10, 10);
		layout.Style = ParticleTexture::Circle;
		layout.Scale = particleScale;
		layout.TexturePath = "Assets\\Textures\\Mario.png";

		mParticleSystem = new ParticleSystem(emmitterPos, layout, 150);
		mParticleSystem->SetRate(3);
		mParticleSystem->SetGravity(0.4f);
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
