#pragma once 
#include "Enemy/EnemySpaceShip.h"

namespace ly {
	class BulletShooter;
	class Hexagon : public EnemySpaceShip {
	public:
		Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyRed4.png", const sf::Vector2f& velocity = {0, 90.f});
		virtual void Tick(float DeltaTime) override;
	private:
		virtual void Shoot();
		unique<BulletShooter> mShooter1;
		unique<BulletShooter> mShooter2;
		unique<BulletShooter> mShooter3;
		unique<BulletShooter> mShooter4;
		unique<BulletShooter> mShooter5;
		unique<BulletShooter> mShooter6;
	};
}