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

ly::Shooter::Shooter(Actor* owner): mOwner (owner)
{
}