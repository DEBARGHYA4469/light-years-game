#pragma once 
#include "framework/Actor.h"

namespace ly {
	class SpaceShip : public Actor {
	public:
		SpaceShip(World* owningWorld);
		SpaceShip(World* owningWorld, const std::string& texturePath);
		virtual void Tick(float deltaTime) override;
		void setVelocity(sf::Vector2f newVelocity);
		sf::Vector2f getVelocity() const;
		virtual void Shoot();
		virtual void BeginPlay() override;
	private:
		sf::Vector2f mVelocity;
	};
}