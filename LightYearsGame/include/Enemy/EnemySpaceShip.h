#pragma once
#include "spaceship/SpaceShip.h"
#include "player/Reward.h"

namespace ly {
	class EnemySpaceShip : public SpaceShip {
	public:
		EnemySpaceShip(World* owningWorld, 
			const std::string& texturePath = "", 
			float mCollisionDamage = 200.f,
			const List<RewardFactoryFunction>& rewardfactories = 
			{
				&RewardFactory::CreateHealthReward,
				&RewardFactory::CreateFrontalWiperReward,
				&RewardFactory::CreateThreeWayShooterReward,
				&RewardFactory::CreateRewardLife
			}
		);
		virtual void Tick(float DeltaTime) override;
		void SetScoreAwardAmt(float Amt);
		void SetRewardSpawnWeight(float weight);
	private:
		float mCollisionDamage;
		float mScoreAwardAmt;
		float mRewardSpawnWeight;
		virtual void OnActorBeginOverlap(Actor* actor) override;
		virtual void Blew() override;
		void SpawnReward();
		List<RewardFactoryFunction> mRewardFactories;
	};
};