#pragma once 
#include "framework/Actor.h"

namespace ly {
	class Particle : public Actor {
	public:
		Particle(World* owningWorld, const std::string texturePath = "");
		virtual void Tick(float DeltaTime) override;
		void RandomVelocity(float minSpeed, float maxSpeed);
		void RandomSize(float min, float max);
		void RandomLifeTime(float min, float max);
		void Move(float DeltaTime);
		void Fade(float DeltaTime);
	private: 
		sf::Vector2f mVelocity;
		float mLifeTime;
		sf::Clock mTimer;
	};
};