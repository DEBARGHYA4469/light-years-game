#include "spaceship/SpaceShip.h"

ly::SpaceShip::SpaceShip(World* owningWorld, const std::string& texturePath):
	Actor(owningWorld, texturePath), mVelocity{}
{
}

void ly::SpaceShip::Tick(float deltaTime)
{
	//LOG("Space Ship Tick ...");
	Actor::Tick(deltaTime);
	AddActorLocationOffset(getVelocity() * deltaTime);
}

void ly::SpaceShip::setVelocity(sf::Vector2f newVelocity)
{
	mVelocity = newVelocity;
}

sf::Vector2f ly::SpaceShip::getVelocity() const
{
	return mVelocity;
}

void ly::SpaceShip::Shoot()
{
}
