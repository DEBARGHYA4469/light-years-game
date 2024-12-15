#include "weapon/BulletShooter.h"
#include "framework/Core.h"

ly::BulletShooter::BulletShooter(Actor* owner, float coolDownTime):
	Shooter(owner), mCoolDownClock{}
{
	mCoolDownTime = coolDownTime;
}

bool ly::BulletShooter::CanShoot() const
{
	return true;
}

bool ly::BulletShooter::IsOnCoolDown() const
{
	if (mCoolDownClock.getElapsedTime().asSeconds() > mCoolDownTime) {
		return false;
	}
	return true;
}

void ly::BulletShooter::ShootImpl()
{
	mCoolDownClock.restart();
	LOG("Shooting ...");
}
