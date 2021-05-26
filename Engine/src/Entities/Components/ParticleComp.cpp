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
	}


	void ParticleComp::Init()
	{
		mType = TYPE::COMPONENT_PARTICLE;

		vec2f emmitterPos = mParent->GetComponent<TransformComp>()->GetPosition();
		vec2f particleScale = mParent->GetComponent<TransformComp>()->GetScale();

		//ParticleSystem(const vec2f & emmitterPos, const Particle & particle, size_t count, const Emmitter & emmiter = Emmitter::Square);
		Particle layout;
		layout.Lifetime = 3; // 3 seconds
		layout.Alive = false; // 3 seconds
		layout.Velocity = vec2f(10, 10);
		layout.Style = ParticleTexture::Custom;
		layout.Scale = particleScale;

		mParticleSystem = new ParticleSystem(emmitterPos, layout, 150);
		mParticleSystem->SetRate(10);
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
