#pragma once 
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly{
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* owner, float coolDownTime = 0.2f, const sf::Vector2f& localPositionOffset = { 0.f, 0.f }, float localRotationOffset = 0.f);
		virtual bool CanShoot() const override;
		virtual bool IsOnCoolDown() const override;
	private: 
		sf::Clock mCoolDownClock;
		float mCoolDownTime; 

		// Inherited via Shooter
		virtual void ShootImpl() override;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
	};
};