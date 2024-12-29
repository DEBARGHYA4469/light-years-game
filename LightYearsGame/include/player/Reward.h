#pragma once 
#include "framework/Actor.h"
#include <functional>

// We want a Enemy space ship to hold list of reward types and spawn a random reward as it is 
// destroyed but in C++ you cannot store a list of types in its base class list and get the type information at runtime. 
// This is called Reflection, RTTI

namespace ly {
	class PlayerSpaceShip;
	class Reward;
	using RewardFactoryFunction = std::function<weak<Reward>(World*)>;
	using RewardFunction = std::function<void(PlayerSpaceShip*)>;
	class Reward : public Actor {
	public:
		Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed = 200.f);
		virtual void BeginPlay() override;
		void Tick(float DeltaTime) override;
		friend class RewardFactory;
	private:
		virtual void OnActorBeginOverlap(Actor* actor) override;
		virtual void OnActorEndOverlap(Actor* actor) override;
		float mSpeed;
		RewardFunction mRewardFunction;
	};

	class RewardFactory {
	public:
		static weak<Reward> CreateHealthReward(World* world);
		static weak<Reward> CreateThreeWayShooterReward(World* world);
		static weak<Reward> CreateFrontalWiperReward(World* world);
		static weak<Reward> CreateReward(World* world, const std::string& texturepath, RewardFunction rewardFunction);
	private:
		static void RewardHealth(PlayerSpaceShip* player);
		static void RewardThreeWayShooter(PlayerSpaceShip* player);
		static void RewardFrontalWiper(PlayerSpaceShip* player);
	};

	
}