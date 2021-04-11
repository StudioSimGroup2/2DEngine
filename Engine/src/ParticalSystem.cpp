#include "ParticalSystem.h"

#if GRAPHICS_LIBRARY == 0 //DX11
ParticleSystem::ParticleSystem()
	: mDevice(nullptr), mPosition(vec2f(100, 100)), mSize(vec2f(100, 100)), mParticleProperties(), mParticleCount(0), mEmmiter(Emmitter::Square)
{
	srand(time(NULL));
	mGravity = 0.0f;
	mRate = 0.0f;
	mCurrentRate = 0.0f;
}

ParticleSystem::ParticleSystem(D3D11Device* device, const vec2f& emmitterPos, const ParticleProperties& particle, size_t count, const Emmitter& emmiter)
	: mDevice(device), mPosition(emmitterPos), mParticleProperties(particle), mParticleCount(count), mEmmiter(emmiter)
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

ParticleSystem::ParticleSystem(D3D11Device* device, const vec2f& emmitterPos, const vec2f& emmitterSize, const ParticleProperties& particle, size_t count, const Emmitter& emmiter)
	: mDevice(device), mPosition(emmitterPos), mSize(emmitterSize), mParticleProperties(particle), mParticleCount(count), mEmmiter(emmiter)
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
		if (p)
			delete p->Texture;
	}
	mParticles.clear();

	if (mParticleProperties.Texture)
		delete mParticleProperties.Texture;

	delete mEmmiterIcon;
}

void ParticleSystem::Update(float dt)
{
	mCurrentRate += dt;

	// Update the icons location
	switch (mEmmiter)
	{
	case Emmitter::Square:
		mEmmiterIcon->SetPosition(&vec2f(mPosition.x + mSize.x / 2, mPosition.y + mSize.y / 2));
		break;

	case Emmitter::Circle:
		mEmmiterIcon->SetPosition(&mPosition);
		break;
	}

	// Update all the particles
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

			switch (mEmmiter) {
			case Emmitter::Square:
				p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y); // Respawn in area of square
				break;

			case Emmitter::Circle:
				float rad = mSize.x * sqrtf(rand() % 11 * 0.1f);	// Returns a value between 0 - 1
				float theta = (rand() % 11 * 0.1f) * 2 * 3.14159265359;
				p->Position.x = mPosition.x + rad * cos(theta);
				p->Position.y = mPosition.y + rad * sin(theta);
				break;
			}
		}

		p->Velocity.y += mGravity * dt;
		p->Position += p->Velocity * dt;
		p->Texture->SetPosition(&p->Position);
	}

}

void ParticleSystem::Render()
{
	for (ParticleProperties* p : mParticles) {
		if (p->Alive)
			p->Texture->Draw();
	}

	if (mShowEmmiterIcon)
		mEmmiterIcon->Draw();
}

void ParticleSystem::InitParticles(size_t count)
{
	switch (mEmmiter)
	{
	case Emmitter::Square: {

		Texture* tex = AssetManager::GetInstance()->LoadTexture("Square", "Assets\\Textures\\Particle System Inbuilt\\Square.dds");

		for (int i = 0; i < count; i++) {


			ParticleProperties* p = new ParticleProperties(mParticleProperties);
			p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y);
			p->Texture = new Sprite("Partical System:", &p->Position, tex);
			D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
			p->Texture->AddRendererComponent();
			mParticles.push_back(p);
		}

		// Setup the Emmiter icon
		Texture* icon = AssetManager::GetInstance()->LoadTexture("SquareIcon", "Assets\\Textures\\Particle System Inbuilt\\SquareEmmiterIcon.dds");
		D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
		mEmmiterIcon = new Sprite("Partical system:", &mPosition, icon);
		mEmmiterIcon->AddRendererComponent();
		break;
	}

	case Emmitter::Circle:
	{
		Texture* tex = AssetManager::GetInstance()->LoadTexture("Circle", "Assets\\Textures\\Particle System Inbuilt\\Circle.dds");

		for (int i = 0; i < count; i++) {
			ParticleProperties* p = new ParticleProperties(mParticleProperties);

			// Generate random point inside circle
			float rad = mSize.x * sqrtf(rand() % 11 * 0.1f);
			float theta = (rand() % 11 * 0.1f) * 2 * 3.14159265359;

			// Convert to cartesian coords
			p->Position.x = mPosition.x + rad * cos(theta);
			p->Position.y = mPosition.y + rad * sin(theta);
			p->Texture = new Sprite("Partical System:", &p->Position, tex);

			D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
			p->Texture->AddRendererComponent();
			mParticles.push_back(p);
		}

		Texture* icon = AssetManager::GetInstance()->LoadTexture("SquareIcon", "Assets\\Textures\\Particle System Inbuilt\\CircleEmmiterIcon.dds");
		// Setup the Emmiter icon
		D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
		mEmmiterIcon = new Sprite("Partical system:", &mPosition, icon);
		mEmmiterIcon->AddRendererComponent();
		break;
	}

	case Emmitter::Cone:
		std::cout << "Cone partical emmision currently not supported!" << std::endl;
		assert(false);
		break;

	}
}
#endif

