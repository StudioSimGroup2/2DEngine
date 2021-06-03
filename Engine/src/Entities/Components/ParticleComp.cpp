#include "ParticleComp.h"
#include "..\GameObject.h"

namespace Engine {

	ParticleComp::ParticleComp() : Component()
	{
		Init();
	}

	ParticleComp::ParticleComp(GameObject* parent)
	{
		//mParent->Attach(parent);
		mParent = parent;
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
		layout.Lifetime = 3; 
		layout.Alive = false;
		layout.Velocity = vec2f(0, -200);
		layout.Style = ParticleTexture::Circle;
		layout.Scale = particleScale;
		layout.TexturePath = "Assets\\Textures\\Mario.png";

		mParticleSystem = new ParticleSystem(emmitterPos, layout, 150);
		mParticleSystem->SetRate(0.1); // particles per second
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
