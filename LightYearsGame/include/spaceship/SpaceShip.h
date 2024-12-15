#pragma once 
#include "framework/Actor.h"

namespace ly {
	class SpaceShip : public Actor {
	public:
		SpaceShip(World* owningWorld, const std::string& texturePath);
		virtual void Tick(float deltaTime) override;
		void setVelocity(sf::Vector2f newVelocity);
		sf::Vector2f getVelocity() const;
	private:
		sf::Vector2f mVelocity;
	};
}