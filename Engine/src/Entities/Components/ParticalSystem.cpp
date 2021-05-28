#include "ParticalSystem.h"
#include <Utils\AssetManager.h>

#if GRAPHICS_LIBRARY == 0 //DX11
namespace Engine
{
	ParticleSystem::ParticleSystem()
		: mPosition(vec2f(100, 100)), mSize(vec2f(100, 100)), mParticleProperties(), mParticleCount(0), mEmmiter(Emmitter::Square)
	{
		srand(time(NULL));
		mGravity = 0.0f;
		mRate = 0.0f;
		mCurrentRate = 0.0f;
	}
	
	ParticleSystem::ParticleSystem(const vec2f& emmitterPos, const Particle& particle, size_t count, const Emmitter& emmiter)
		:  mPosition(emmitterPos), mParticleProperties(particle), mParticleCount(count), mEmmiter(emmiter)
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
	
	ParticleSystem::ParticleSystem(const vec2f& emmitterPos, const vec2f& emmitterSize, const Particle& particle, size_t count, const Emmitter& emmiter)
		: mPosition(emmitterPos), mSize(emmitterSize), mParticleProperties(particle), mParticleCount(count), mEmmiter(emmiter)
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
		//for (Particle* p : mParticles) {
		//	//if (p)		// We dont delete textures...
		//	//	delete p->Texture;
		//}
		mParticles.clear();
	
		//delete mEmmiterIcon; // Cannot delete atm because its sprite takes a pointer to a position 
	}

	void ParticleSystem::Init()
	{
		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));
	}

	void ParticleSystem::Update()
	{
#define DT 0.016f
		mCurrentRate += DT; // TODO: Requires DT

		// Update the emmiter icons location
		//switch (mEmmiter)
		//{
		//case Emmitter::Square: mEmmiterIcon->SetPosition(mParent->GetComponent<TransformComp>()->GetPosition()); break;	// Need to get parent Transform Component for position
		//case Emmitter::Circle: mEmmiterIcon->SetPosition(&mPosition); break;
		//case Emmitter::Cone: mEmmiterIcon->SetPosition(&mPosition); break;
		//}

		// Update all the particles
		for (Particle* p : mParticles) {
			if (!p->Alive) {
				if (mCurrentRate >= mRate) {
					p->Alive = true;
					mCurrentRate = 0;
				}
				continue;
			}

			p->Lifetime -= DT;

			// If a particle is "dead"
			if (p->Lifetime <= 0.0f) {
				p->Alive = false;
				p->Velocity = mParticleProperties.Velocity;
				p->Lifetime = mParticleProperties.Lifetime;
				p->Scale = mParticleProperties.Scale;
				SetupTexture(p);

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

			p->Velocity.y += mGravity * DT;
			p->Position += p->Velocity * DT;
			
		}

	}

	void ParticleSystem::Render()
	{
		for (Particle* p : mParticles) {
			if (p->Alive) {
				if (!mRenderer)
					return;

#if GRAPHICS_LIBRARY == 0
				dynamic_cast<D3D11Renderer2D*>(mRenderer)->Draw(p->Position, vec2f(0,0), p->Scale, p->Texture);
#elif GRAPHICS_LIBRARY == 1
				dynamic_cast<OGLRenderer2D*>(mRenderer)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
					mParent->GetComponent<TransformComp>()->GetRotation(),
					mParent->GetComponent<TransformComp>()->GetScale(),
					p->Texture
				);
#endif
			}
		}

		//if (mShowEmmiterIcon)
		//	mEmmiterIcon->Draw();

		//dynamic_cast<OGLRenderer2D*>(mRenderer)->Draw(mParent->GetComponent<TransformComp>()->GetPosition(),
		//	mParent->GetComponent<TransformComp>()->GetRotation(),
		//	mParent->GetComponent<TransformComp>()->GetScale(),
		//	p->Texture
		//);
	}

	void ParticleSystem::SetParticleCount(int newSize)
	{
		int diff = newSize - mParticleCount;
		if (newSize > mParticleCount)
		{
			for (int i = 0; i < diff; i++) {
				switch (mEmmiter)
				{
					case Emmitter::Square: {
						Particle* p = new Particle(mParticleProperties);
						p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y);

						SetupTexture(p);

						mParticles.push_back(p);

						// Setup the Emmiter icon
						//Texture* icon = AssetManager::GetInstance()->LoadTexture("SquareIcon", "Assets\\Textures\\Particle System Inbuilt\\SquareEmmiterIcon.dds");
						//D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
						//mEmmiterIcon = new Sprite("Partical system:", &mPosition, icon);
						//mEmmiterIcon->AddRendererComponent();
						break;
					}
				}
			}
		}
		else {
			diff *= -1; // Convert to positive so we can for-loop
			mParticles.erase(mParticles.begin(), mParticles.begin() + diff);
		}

		mParticleCount = newSize;
		Logger::LogMsg("Particle size", mParticles.size());
		Logger::LogMsg("Particle cap", mParticles.capacity());
	}


	void ParticleSystem::InitParticles(size_t count)
	{
		if (mRenderer == nullptr)
			mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));


		switch (mEmmiter)
		{
		case Emmitter::Square: {

			for (int i = 0; i < count; i++) {
				Particle* p = new Particle(mParticleProperties);
				p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y);
		
				SetupTexture(p);

				mParticles.push_back(p);
			}

			// Setup the Emmiter icon
			//Texture* icon = AssetManager::GetInstance()->LoadTexture("SquareIcon", "Assets\\Textures\\Particle System Inbuilt\\SquareEmmiterIcon.dds");
			//D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
			//mEmmiterIcon = new Sprite("Partical system:", &mPosition, icon);
			//mEmmiterIcon->AddRendererComponent();
			break;
		}

		case Emmitter::Circle:
		{
			Texture* tex = AssetManager::GetInstance()->LoadTexture("Circle", "Assets\\Textures\\Particle System Inbuilt\\Circle.dds");

			for (int i = 0; i < count; i++) {
				Particle* p = new Particle(mParticleProperties);

				// Generate random point inside circle
				float rad = mSize.x * sqrtf(rand() % 11 * 0.1f);
				float theta = (rand() % 11 * 0.1f) * 2 * 3.14159265359;

				// Convert to cartesian coords
				p->Position.x = mPosition.x + rad * cos(theta);
				p->Position.y = mPosition.y + rad * sin(theta);

				SetupTexture(p);


				//D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
				//p->Texture->AddRendererComponent();
				mParticles.push_back(p);
			}

			//Texture* icon = AssetManager::GetInstance()->LoadTexture("SquareIcon", "Assets\\Textures\\Particle System Inbuilt\\CircleEmmiterIcon.dds");
			// Setup the Emmiter icon
			//D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
			//mEmmiterIcon = new Sprite("Partical system:", &mPosition, icon);
			//mEmmiterIcon->AddRendererComponent();
		//	break;
		}

		case Emmitter::Cone:
			std::cout << "Cone partical emmision currently not supported!" << std::endl;
			assert(false);
			break;

		}
	}

	void ParticleSystem::SetupTexture(Particle* particle)
	{
		Texture* tex = nullptr;
		switch (mParticleProperties.Style)
		{
		case ParticleTexture::Custom: {
			tex = AssetManager::GetInstance()->LoadTexture("Custom", mParticleProperties.TexturePath);
			break;
		}
		case ParticleTexture::Circle: {
			tex = AssetManager::GetInstance()->LoadTexture("Circle", "Assets\\Textures\\Particle System Inbuilt\\Circle.png");
			break;
		}
		case ParticleTexture::Square: {
			tex = AssetManager::GetInstance()->LoadTexture("Square", "Assets\\Textures\\Particle System Inbuilt\\Square.png");
			break;
		}
		case ParticleTexture::Triangle: {
			tex = AssetManager::GetInstance()->LoadTexture("Triangle", "Assets\\Textures\\Particle System Inbuilt\\Triangle.png");
			break;
		}
		}

		particle->Texture = tex;
		mParticleProperties.Texture = tex;
	}
}
#endif

