#pragma once 
#include "Enemy/EnemySpaceShip.h"

namespace ly {
	class BulletShooter;
	class UFO : public EnemySpaceShip {
	public:
		UFO(World* world, const sf::Vector2f& velocity = { 0.f, 0.f }, const std::string texturePath = "SpaceShooterRedux/PNG/ufoYellow.png", float rotationSpeed = 40.f);
		virtual void Tick(float DeltaTime) override;
	private:
		virtual void Shoot();
		unique<BulletShooter> mshooter1;
		unique<BulletShooter> mshooter2;
		unique<BulletShooter> mshooter3;
		float mRotationSpeed;
	};
};