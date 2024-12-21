#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
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

	// bullets are only destroyed when game ends, lots of ghosts bullets.
	weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserGreen06.png");
	newBullet.lock()->setActorLocation(GetOwner()->GetActorLocation());
	newBullet.lock()->setActorRotation(GetOwner()->GetActorRotation());
}
