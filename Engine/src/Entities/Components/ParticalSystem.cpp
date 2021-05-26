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
		for (Particle* p : mParticles) {
			if (p)
				delete p->Texture;
		}
		mParticles.clear();
	
		//delete mEmmiterIcon; // Cannot delete atm because its sprite takes a pointer to a position 
	}

	void ParticleSystem::Init()
	{
		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));
		//mType = "Sprite";
	}

	void ParticleSystem::Update()
	{
		//mCurrentRate += dt;
		mCurrentRate += 0.16f; // TODO: Requires DT

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

			//p->Lifetime -= dt;
			p->Lifetime -= 0.16f;

			// If a partical is "dead"
			if (p->Lifetime <= 0.0f) {
				p->Alive = false;
				p->Velocity = mParticleProperties.Velocity;
				p->Lifetime = mParticleProperties.Lifetime;
				p->Scale = mParticleProperties.Scale;

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

			//p->Velocity.y += mGravity * dt;
			//p->Position += p->Velocity * dt;

			// TODO: Requires DT
			p->Velocity.y += mGravity * 0.16f;
			p->Position += p->Velocity * 0.16f;
			
		}

	}

	void ParticleSystem::Render()
	{
		for (Particle* p : mParticles) {
			if (p->Alive) {
				//p->Texture->Draw();
				if (!mRenderer)
					return;

#if GRAPHICS_LIBRARY == 0
				dynamic_cast<D3D11Renderer2D*>(mRenderer)->Draw(p->Position, vec2f(0,0), vec2f(p->Scale.x, p->Scale.y), p->Texture);
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

	void ParticleSystem::InitParticles(size_t count)
	{
		mRenderer = Device::CreateRenderer(AssetManager::GetInstance()->GetShaderByName("Default"));

		switch (mEmmiter)
		{
		case Emmitter::Square: {

			for (int i = 0; i < count; i++) {


				Particle* p = new Particle(mParticleProperties);
				p->Position = vec2f(rand() % (int)mSize.x + mPosition.x, rand() % (int)mSize.y + mPosition.y);
		
				SetupTexture(p);

				//D3D11Renderer2D* re = new D3D11Renderer2D(static_cast<D3D11Shader*>(AssetManager::GetInstance()->GetShaderByName("Default")), mDevice);
				//p->Texture->AddRendererComponent();
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

		switch (particle->Style)
		{
		case ParticleTexture::Custom: {
			Texture* tex = AssetManager::GetInstance()->LoadTexture("Square", "Assets\\Textures\\Particle System Inbuilt\\Square.png");
			particle->Texture = tex;
			break;
		}
		//case ParticleTexture::Circle: particle->Texture = new Texture("Partical system:", &particle->Position, "Inbuilt Circle Tex", "Resources\\Textures\\Particle System Inbuilt\\Circle.dds"); break;
		//case ParticleTexture::Square: particle->Texture = new Texture("Partical system:", &particle->Position, "Inbuilt Square Tex", "Resources\\Textures\\Particle System Inbuilt\\Square.dds"); break;
		//case ParticleTexture::Triangle: particle->Texture = new Texture("Partical system:", &particle->Position, "Inbuilt Triangle Tex", "Resources\\Textures\\Particle System Inbuilt\\Triangle.dds"); break;
		}
	}
}
#endif

