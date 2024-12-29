#include "player/Reward.h" 
#include "player/PlayerSpaceShip.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly {

	Reward::Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed)
	: Actor(world, texturePath),
		mRewardFunction(rewardFunction),
		mSpeed(speed)
	{
	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float DeltaTime) {
		Actor::Tick(DeltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * DeltaTime });
	}

	void Reward::OnActorBeginOverlap(Actor* other)
	{
		// TODO : clean up casting, dynamic cast is slower, RTTI
		PlayerSpaceShip* playerSpaceShip = dynamic_cast<PlayerSpaceShip*>(other);
		if (playerSpaceShip != nullptr && !playerSpaceShip->isPendingDestroy()) {
			mRewardFunction(playerSpaceShip);
			Destroy();
		}
		
	}
	void Reward::OnActorEndOverlap(Actor* actor)
	{

	}
	
	weak<Reward> RewardFactory::CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", &RewardHealth);
	}

	weak<Reward> RewardFactory::CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", &RewardThreeWayShooter);
	}

	weak<Reward> RewardFactory::CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", &RewardFrontalWiper);
	}

	weak<Reward> RewardFactory::CreateReward(World* world, const std::string& texturepath, RewardFunction rewardFunction)
	{
		return world->SpawnActor<Reward>(texturepath, rewardFunction);
	}

	

	void RewardFactory::RewardHealth(PlayerSpaceShip* player)
	{
		static float rewardAmount = 10.f; // once upgraded all other places it gets the upgraded delta!! 
		if (player && !player->isPendingDestroy()) {
			player->GetHealthComponent().ChangeHealth(rewardAmount);
		}
	}
	void RewardFactory::RewardThreeWayShooter(PlayerSpaceShip* player)
	{
		if (player && !player->isPendingDestroy()) {
			auto weapon = unique<Shooter>(new ThreeWayShooter(player));
			player->SetShooter(std::move(weapon));
		}
	}
	void RewardFactory::RewardFrontalWiper(PlayerSpaceShip* player)
	{
		if (player && !player->isPendingDestroy()) {
			auto weapon = unique<Shooter>(new FrontalWiper(player));
			player->SetShooter(std::move(weapon));
		}
	}
};