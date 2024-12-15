#pragma once 
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly{
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* owner, float coolDownTime = 0.1f);
		virtual bool CanShoot() const override;
		virtual bool IsOnCoolDown() const override;
	private: 
		sf::Clock mCoolDownClock;
		float mCoolDownTime; 

		// Inherited via Shooter
		virtual void ShootImpl() override;
	};
};