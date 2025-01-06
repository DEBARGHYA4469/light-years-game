#include "weapon/FrontalWiper.h"

ly::FrontalWiper::FrontalWiper(Actor* owner, float coolDownTime, const sf::Vector2f& localOffset, float width) :
	Shooter(owner),
	mShooter1{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{0, -width / 2.f}, -1.f) },
	mShooter2{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{0, -width / 6.f}, 0.f) },
	mShooter3{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{0, +width / 6.f}, 0.f) },
	mShooter4{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{0, +width / 2.f}, 1.f) },
	mShooter5{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{0, -width / 1.5f}, -0.5f) },
	mShooter6{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{0, +width / 1.5f}, +0.5f) },

	mWidth(width)
{
	mShooter1->SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen11.png");
	mShooter2->SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserBlue07.png");
	mShooter3->SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserBlue07.png");
	mShooter4->SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen11.png");

	mShooter5->SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen11.png");
	mShooter6->SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserGreen11.png");
}

void ly::FrontalWiper::ShootImpl()
{
	mShooter1->Shoot();
	mShooter2->Shoot();
	mShooter3->Shoot();
	mShooter4->Shoot();

	if (GetCurrentLevel() == GetMaxLevel()) {
		mShooter5->Shoot();
		mShooter6->Shoot();
	}
}

void ly::FrontalWiper::IncrementLevel(int Amt)
{
	Shooter::IncrementLevel(Amt);
	mShooter1->IncrementLevel(Amt);
	mShooter2->IncrementLevel(Amt);
	mShooter3->IncrementLevel(Amt);
	mShooter4->IncrementLevel(Amt);
	mShooter5->IncrementLevel(Amt);
	mShooter6->IncrementLevel(Amt);
}

void ly::FrontalWiper::SetCurrentLevel(int Level)
{
	Shooter::SetCurrentLevel(Level);
	mShooter1->SetCurrentLevel(Level);
	mShooter2->SetCurrentLevel(Level);
	mShooter3->SetCurrentLevel(Level);
	mShooter4->SetCurrentLevel(Level);
	mShooter5->SetCurrentLevel(Level);
	mShooter6->SetCurrentLevel(Level);
}
