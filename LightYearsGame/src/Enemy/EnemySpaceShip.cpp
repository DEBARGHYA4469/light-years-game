#include "Enemy/EnemySpaceShip.h"
#include "player/Reward.h"

ly::EnemySpaceShip::EnemySpaceShip(World* owningWorld, 
	const std::string& texturePath, 
	float mCollisionDamage,
	const List<RewardFactoryFunction>& rewardfactories):
	SpaceShip(owningWorld, texturePath),
	mCollisionDamage(mCollisionDamage),
	mRewardFactories(rewardfactories)
{

}

void ly::EnemySpaceShip::Tick(float DeltaTime)
{
	SpaceShip::Tick(DeltaTime);
	if (IsActorOutOfWindowBounds(std::max(GetActorGlobalBounds().width, GetActorGlobalBounds().height) * 2.f)) {
		Destroy();
	} 
}

void ly::EnemySpaceShip::OnActorBeginOverlap(Actor* other)
{
	SpaceShip::OnActorBeginOverlap(other);
	if (isOtherHostile(other)) {
		other->ApplyDamage(mCollisionDamage);
	}
}

void ly::EnemySpaceShip::Blew()
{
	SpawnReward();
}

void ly::EnemySpaceShip::SpawnReward()
{	
	if (!mRewardFactories.size()) return;
	int pick = (int) RandomRange(0, mRewardFactories.size());
	if (pick >= 0 && pick < mRewardFactories.size()) {
		auto reward = mRewardFactories[pick](GetWorld());
		reward.lock()->SetActorLocation(GetActorLocation());
	}
}
