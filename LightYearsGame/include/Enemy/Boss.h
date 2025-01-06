#pragma once 
#include "Enemy/EnemySpaceShip.h"
#include "weapon/BulletShooter.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ly {
	class Boss : public EnemySpaceShip {
	public:
		Boss(World* world);
		virtual void Tick(float Deltatime) override;
		void CheckMove();
		virtual void BeginPlay() override;
	private:
		float mSpeed; 
		float mBaseSpeed;
		float mSwitchDistanceToEdge;

		unique<BulletShooter> mBaseShooterLeft;
		unique<BulletShooter> mBaseShooterRight;
		unique<ThreeWayShooter> mThreeWayShooter;
		unique<FrontalWiper> mFrontalWiperLeft;
		unique<FrontalWiper> mFrontalWiperRight;

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWiper();
		void HealthChanged(float amt, float curr, float maxHealth);

		int mStage;
		void SetStage(int stage);
		void IncreaseStage();
	};
};