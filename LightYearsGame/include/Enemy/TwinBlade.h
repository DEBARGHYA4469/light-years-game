#pragma once 
#include "Enemy/EnemySpaceShip.h"

namespace ly {
	class BulletShooter;
	class TwinBlade : public EnemySpaceShip {
	public:
		TwinBlade(World* owningWorld, const sf::Vector2f& velocity = { 0.f, 150.f }, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png");
		virtual void Tick(float DeltaTime) override;
	private:
		virtual void Shoot() override;
		unique<BulletShooter> mShooterLeft;
		unique<BulletShooter> mShooterRight;
	};
};