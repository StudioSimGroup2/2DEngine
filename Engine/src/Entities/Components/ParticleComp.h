#pragma once
#include "Entities/GameObject.h"
#include "Utils/Texture.h"


namespace Engine {

	enum class ParticleTexture
	{
		Custom = 0,
		Circle,
		Square,
		Triangle
	};

	struct Particle
	{
	public:

		Particle();
		~Particle();	


		vec2f Position;		/* Local position of a single partical */
		vec2f Velocity;
		float Lifetime;		/* Measured in Seconds */
		const char* TexturePath;
		bool Alive;
		ParticleTexture Style;
		Texture* Texture;
	private:
	};

}

