#include "weapon/Bullet.h"

namespace ly {
	Bullet::Bullet(World* world, Actor* owner, const std::string& path, float speed, float damage):
		Actor(world, path), mOwner(owner), mSpeed(speed), mDamage(damage)
	{
		SetTeamID(owner->GetTeamID());
	}
	void Bullet::SetSpeed(float newSpeed)
	{
		mSpeed = newSpeed;
	}
	void Bullet::SetDamage(float newDamage)
	{
		mDamage = newDamage;
	}
	void Bullet::Tick(float DeltaTime)
	{
		Actor::Tick(DeltaTime);
		Move(DeltaTime);
		if (IsActorOutOfWindowBounds()) {
			Destroy();
		}
	}
	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Bullet::OnActorBeginOverlap(Actor* actor)
	{
		if (isOtherHostile(actor)) {
			actor->ApplyDamage(GetDamage());
			Destroy();
		}
	}
	void Bullet::OnActorEndOverlap(Actor* actor)
	{

	}

	void Bullet::Move(float DeltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * mSpeed * DeltaTime);
	}
};