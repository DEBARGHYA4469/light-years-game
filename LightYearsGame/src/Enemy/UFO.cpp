#include "Enemy/UFO.h"
#include "weapon/BulletShooter.h"

ly::UFO::UFO(World* world, const sf::Vector2f& velocity, const std::string texturePath, float rotationSpeed)
:EnemySpaceShip(world, texturePath),
mshooter1{ new BulletShooter(this, 1.f, {0.f, 0.f}, -20.f) },
mshooter2{ new BulletShooter(this, 1.f, {0.f, 0.f}, 90.f) },
mshooter3{ new BulletShooter(this, 1.f, {0.f, 0.f}, 200.f) },
mRotationSpeed{rotationSpeed}
{
	SetVelocity(velocity);
	SetTeamID(2);
	SetScoreAwardAmt(30);
}

void ly::UFO::Tick(float DeltaTime)
{
	EnemySpaceShip::Tick(DeltaTime);
	Shoot();
	AddActorRotationOffset(mRotationSpeed * DeltaTime);
}

void ly::UFO::Shoot()
{
	mshooter1->Shoot();
	mshooter2->Shoot();
	mshooter3->Shoot();
}
