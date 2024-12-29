#include <Enemy/Hexagon.h>
#include <weapon/BulletShooter.h>

// Bullet Shooter: <World, CoolDown, LocationOffset, RotationOffset>
ly::Hexagon::Hexagon(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
	: EnemySpaceShip(owningWorld, texturePath),
	mShooter1{ new BulletShooter(this,1.f, sf::Vector2f{-40.f, -50.f}, - 130.f) },
	mShooter2{ new BulletShooter(this,1.f, sf::Vector2f{30.f, -60.f}, - 60.f) },
	mShooter3{ new BulletShooter(this,1.f, sf::Vector2f{50.f, -10.f}, -10.f) },
	mShooter4{ new BulletShooter(this,1.f, sf::Vector2f{50.f, 10.f}, 10.f) },
	mShooter5{ new BulletShooter(this,1.f, sf::Vector2f{30.f, 60.f}, + 60.f) },
	mShooter6{ new BulletShooter(this,1.f, sf::Vector2f{-40.f, 50.f}, + 130.f) }
{
	SetTeamID(2);
	setVelocity(velocity);
}

void ly::Hexagon::Tick(float DeltaTime)
{
	EnemySpaceShip::Tick(DeltaTime);
	Shoot();
}

void ly::Hexagon::Shoot()
{
	mShooter1->Shoot();
	mShooter2->Shoot();
	mShooter3->Shoot();
	mShooter4->Shoot();
	mShooter5->Shoot();
	mShooter6->Shoot();
}
