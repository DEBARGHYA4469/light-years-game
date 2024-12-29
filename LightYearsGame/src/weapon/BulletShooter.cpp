#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
#include "framework/Core.h"

ly::BulletShooter::BulletShooter(Actor* owner, float coolDownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& BulletTexturePath)
	:Shooter(owner), 
	mCoolDownTime{coolDownTime},
	mCoolDownClock{},
	mLocalPositionOffset{ localPositionOffset },
	mLocalRotationOffset{ localRotationOffset },
	mBulletTexturePath(BulletTexturePath)
{
	mCoolDownTime = coolDownTime;
}

bool ly::BulletShooter::CanShoot() const
{
	return true;
}

bool ly::BulletShooter::IsOnCoolDown() const
{
	if (mCoolDownClock.getElapsedTime().asSeconds() > mCoolDownTime / GetCurrentLevel()) {
		return false;
	}
	return true;
}

void ly::BulletShooter::IncrementLevel(int Amt)
{
	Shooter::IncrementLevel(Amt);
}

void ly::BulletShooter::ShootImpl()
{
	mCoolDownClock.restart();

	// bullets are only destroyed when game ends, lots of ghosts bullets.
	// bullets direction is relative to the direction pointed by Shooter
	sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
	sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

	weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), mBulletTexturePath);
	newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
	newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
}
