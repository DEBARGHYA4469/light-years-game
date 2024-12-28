#pragma once 
#include "framework/Actor.h"

namespace ly {
	class Bullet : public Actor {
	public:
		Bullet(World* world, Actor* owner, const std::string& path, float speed = 400.f, float damage = 10);
		void SetSpeed(float newSpeed);
		void SetDamage(float newDamage);
		float GetSpeed() const { return mSpeed; }
		float GetDamage() const { return mDamage; }	
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;
		virtual void OnActorBeginOverlap(Actor* actor) override;
		virtual void OnActorEndOverlap(Actor* actor) override;
	private:
		void Move(float DeltaTime);
 		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
};