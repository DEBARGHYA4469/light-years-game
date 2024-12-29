#pragma once 
#include "weapon/Shooter.h"
#include "weapon/BulletShooter.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class FrontalWiper : public Shooter {
	public:
		FrontalWiper(Actor* owner, 
			float coolDownTime = 0.2f, 
			const sf::Vector2f& localOffset = { 50.f, 0.f },
			float width = 60.f);
	private:
		float mWidth;
		virtual void ShootImpl() override;
		virtual void IncrementLevel(int Amt) override;
		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		unique<BulletShooter> mShooter4;

		unique<BulletShooter> mShooter5;
		unique<BulletShooter> mShooter6;

	};
};