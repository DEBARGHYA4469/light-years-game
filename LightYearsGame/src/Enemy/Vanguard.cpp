#include "Enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

ly::Vanguard::Vanguard(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath)
	: EnemySpaceShip(owningWorld, texturePath), mShooter{ new BulletShooter(this, 1.f, {-50.f, 0.f}, 180.f) }
{
	setVelocity(velocity);
	SetTeamID(2);
}

void ly::Vanguard::Tick(float DeltaTime)
{
	EnemySpaceShip::Tick(DeltaTime);
	Shoot();
}

void ly::Vanguard::Shoot()
{
	mShooter->Shoot();
}
