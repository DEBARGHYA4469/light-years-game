#include "weapon/ThreeWayShooter.h"

ly::ThreeWayShooter::ThreeWayShooter(Actor* owner, float coolDownTime, const sf::Vector2f& localOffset):
	Shooter(owner),
	mShooterLeft{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{10, -10}, -10.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png")},
	mShooterMid{ new BulletShooter(owner, coolDownTime, localOffset, -0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png") },
	mShooterRight{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{10, 10}, 10.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png") },
	mTopLevelShooterLeft{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{10, -15}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png") },
	mTopLevelShooterRight{ new BulletShooter(owner, coolDownTime, localOffset + sf::Vector2f{10, 15}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png") }
{

}

void ly::ThreeWayShooter::ShootImpl()
{
	mShooterLeft->Shoot();
	mShooterMid->Shoot();
	mShooterRight->Shoot();

	if (GetCurrentLevel() == GetMaxLevel()) {
		mTopLevelShooterLeft->Shoot();
		mTopLevelShooterRight->Shoot();
	}
}

void ly::ThreeWayShooter::IncrementLevel(int Amt)
{
	Shooter::IncrementLevel(Amt);
	mShooterLeft->IncrementLevel(Amt);
	mShooterMid->IncrementLevel(Amt);
	mShooterRight->IncrementLevel(Amt);

	mTopLevelShooterLeft->IncrementLevel(Amt);
	mTopLevelShooterRight->IncrementLevel(Amt);


}
