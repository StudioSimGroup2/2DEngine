#include "ParticalSystem.h"

ParticleSystem::ParticleSystem()
	: mDevice(nullptr), mPosition(vec2f(100, 100)), mSize(vec2f(100, 100)), mParticleProperties(), mParticleCount(0), mEmmiter(Emmitter::Box)
{
	srand(time(NULL));
	mGravity = 0.0f;
	mRate = 0.0f;
	mCurrentRate = 0.0f;
}

ParticleSystem::ParticleSystem(D3D11Device* device, const vec2f& position, const ParticleProperties& particle, size_t count, const Emmitter& emmiter)
	: mDevice(device), mPosition(position), mParticleProperties(particle), mParticleCount(count), mEmmiter(emmiter)
{
	srand(time(NULL));
	mGravity = 0.0f;
	mRate = 0.0f;
	mCurrentRate = 0.0f;

	mParticleProperties = particle;
	mParticleProperties.Position = mPosition;
	mParticleProperties.Alive = false;
	mSize = vec2f(100, 100);

	InitParticles(mParticleCount);
}

ParticleSystem::ParticleSystem(D3D11Device* device, const vec2f& position, const vec2f& size, const ParticleProperties& particle, size_t count, const Emmitter& emmiter)
	: mDevice(device), mPosition(position), mSize(size), mParticleProperties(particle), mParticleCount(count), mEmmiter(emmiter)
{
	srand(time(NULL));
	mGravity = 0.0f;
	mRate = 0.0f;
	mCurrentRate = 0.0f;

	mParticleProperties = particle;
	mParticleProperties.Position = mPosition;
	mParticleProperties.Alive = false;

	InitParticles(mParticleCount);

}

ParticleSystem::~ParticleSystem()
{
	for (ParticleProperties* p : mParticles) {
		delete p;
	}
	mParticles.clear();

	delete mParticleProperties.Texture;
}

void ParticleSystem::Update(float dt)
{
	mCurrentRate += dt;
	for (ParticleProperties* p : mParticles) {
		if (!p->Alive) {
			if (mCurrentRate >= mRate) {
				p->Alive = true;
				mCurrentRate = 0;
			}
			continue;
		}

		p->Lifetime -= dt;

		// If a partical is "dead"
		if (p->Lifetime <= 0.0f) {
			p->Alive = false;
			p->Velocity = mParticleProperties.Velocity;
			p->Lifetime = mParticleProperties.Lifetime;
			p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y); // Respawn in area of Box atm...
		}

		p->Velocity.y += mGravity * dt;
		p->Position += p->Velocity * dt;
		p->Texture->SetPosition(p->Position);

	}



}

void ParticleSystem::Render()
{
	for (ParticleProperties* p : mParticles) {
		if (p->Alive)
			p->Texture->Draw();
			
	}
}

void ParticleSystem::InitParticles(size_t count)
{
	switch (mEmmiter)
	{
	case Emmitter::Box:
		for (int i = 0; i < count; i++) {
			ParticleProperties* p = new ParticleProperties(mParticleProperties);
			p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y);
			p->Texture = new Sprite(mDevice, "Partical system:", "Textures/stone.dds", p->Position);
			D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
			p->Texture->AddRendererComponent(re);
			mParticles.push_back(p);
		}
		break;

	case Emmitter::Circle:
		std::cout << "Circle partical emmision currently not supported!" << std::endl;
		assert(false);
		break;

	case Emmitter::Cone:
		std::cout << "Cone partical emmision currently not supported!" << std::endl;
		assert(false);
		break;

	}
}