#pragma once
#include "spaceship/SpaceShip.h"

namespace ly {
	class EnemySpaceShip : public SpaceShip {
	public:
		EnemySpaceShip(World* owningWorld, const std::string& texturePath = "", float mCollisionDamage = 200.f);
		virtual void Tick(float DeltaTime) override;
	private:
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* actor) override;
	};
};