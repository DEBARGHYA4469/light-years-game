#pragma once 
#include "spaceship/SpaceShip.h"
#include "framework/MathUtil.h"
#include <framework/TimerManager.h>

namespace ly {
	class Shooter;
	class PlayerSpaceShip : public SpaceShip {
	public:
		PlayerSpaceShip(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip3_orange.png");
		virtual void Tick(float DeltaTime) override;
		void SetSpeed(float newSpeed);
		float GetSpeed()  const { return mSpeed;  }
		virtual void Shoot() override;
		void SetShooter(unique<Shooter>&& shooter); 
		virtual void ApplyDamage(float amt) override;
		virtual void BeginPlay() override;
	private:
		void HandleInput();
		void ConsumeInput(float DeltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();
		void StopInvulnerable();
		void UpdateInvulnerable(float DeltaTime);
		sf::Vector2f mMoveInput;
		float mSpeed;
		unique<Shooter> mShooter;

		float mInvulnerableTime;
		TimerHandle mInvulnerableTimerHandle;
		bool mInVulnerable;
		float mInvulerableFlashInterval;
		float mInvulnerableFlashTimer;
		float mInvulnerableFlashDirection;
	};
};