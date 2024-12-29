#pragma once 
#include "weapon/BulletShooter.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class ThreeWayShooter : public Shooter{
	public:
		ThreeWayShooter(Actor* owner, float coolDownTime = .3f, const sf::Vector2f& localOffset = {50.f, 0.f});
	private:
		unique<BulletShooter> mShooterLeft;
		unique<BulletShooter> mShooterMid;
		unique<BulletShooter> mShooterRight;
		unique<BulletShooter> mTopLevelShooterLeft;
		unique<BulletShooter> mTopLevelShooterRight;

		virtual void ShootImpl();
		virtual void IncrementLevel(int Amt) override;
	};
};