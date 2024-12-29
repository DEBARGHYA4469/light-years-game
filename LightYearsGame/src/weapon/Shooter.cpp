#include "weapon/Shooter.h"
#include "framework/Actor.h"

void ly::Shooter::Shoot()
{
	if (CanShoot() && !IsOnCoolDown()) {
		ShootImpl();
	}
}

bool ly::Shooter::CanShoot() const
{
	return true;
}

bool ly::Shooter::IsOnCoolDown() const
{
	return false;
}

void ly::Shooter::IncrementLevel(int Amt)
{
	mCurrentLevel = std::min(mCurrentLevel + Amt, mMaxLevel);
}

ly::Shooter::Shooter(Actor* owner) : mOwner(owner), mCurrentLevel{ 1 }, mMaxLevel{2}
{
}