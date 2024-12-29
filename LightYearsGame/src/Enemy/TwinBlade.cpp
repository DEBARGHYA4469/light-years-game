#include "Enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

ly::TwinBlade::TwinBlade(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath):
	EnemySpaceShip(owningWorld, texturePath),
	mShooterLeft{ new BulletShooter(this, 1.f, {60.f, -20.f}, 0.f) },
	mShooterRight{ new BulletShooter(this, 1.f, {60.f, 20.f}, 0.f) }
{	
	SetTeamID(2);
	setVelocity(velocity);
}

void ly::TwinBlade::Tick(float DeltaTime)
{
	EnemySpaceShip::Tick(DeltaTime);
	Shoot();
}

void ly::TwinBlade::Shoot()
{
	mShooterLeft->Shoot();
	mShooterRight->Shoot();
}
