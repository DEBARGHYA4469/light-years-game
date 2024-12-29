#pragma once 
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly{
	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* owner, 
			float coolDownTime = 0.2f, 
			const sf::Vector2f& localPositionOffset = { 50.f, 0.f }, 
			float localRotationOffset = 0.f, const std::string& BulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserGreen11.png");
		virtual bool CanShoot() const override;
		virtual bool IsOnCoolDown() const override;
		void SetBulletTexturePath(const std::string& bulletTexturePath) { mBulletTexturePath = bulletTexturePath; }
		virtual void IncrementLevel(int Amt) override;
	private: 
		sf::Clock mCoolDownClock;
		float mCoolDownTime; 

		// Inherited via Shooter
		virtual void ShootImpl() override;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mBulletTexturePath;
	};
};