#pragma once 
#include "spaceship/SpaceShip.h"
#include "framework/MathUtil.h"

namespace ly {
	class BulletShooter;
	class PlayerSpaceShip : public SpaceShip {
	public:
		PlayerSpaceShip(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip3_orange.png");
		virtual void Tick(float DeltaTime) override;
		void SetSpeed(float newSpeed);
		float GetSpeed()  const { return mSpeed;  }
		virtual void Shoot() override;
	private:
		void HandleInput();
		void ConsumeInput(float DeltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();
		sf::Vector2f mMoveInput;
		float mSpeed;
		unique<BulletShooter> mShooter;
	};
};