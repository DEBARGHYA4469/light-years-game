#include "Enemy/EnemySpaceShip.h"
#include "player/Reward.h"
#include "player/PlayerManager.h"

ly::EnemySpaceShip::EnemySpaceShip(World* owningWorld, 
	const std::string& texturePath, 
	float mCollisionDamage,
	const List<RewardFactoryFunction>& rewardfactories):
	SpaceShip(owningWorld, texturePath),
	mCollisionDamage(mCollisionDamage),
	mRewardFactories(rewardfactories),
	mScoreAwardAmt{10},
	mRewardSpawnWeight{0.5f}
{

}

void ly::EnemySpaceShip::Tick(float DeltaTime)
{
	SpaceShip::Tick(DeltaTime);
	if (IsActorOutOfWindowBounds(std::max(GetActorGlobalBounds().width, GetActorGlobalBounds().height) * 2.f)) {
		Destroy();
	} 
}

void ly::EnemySpaceShip::SetScoreAwardAmt(float Amt)
{
	mScoreAwardAmt = Amt;
}

void ly::EnemySpaceShip::SetRewardSpawnWeight(float weight)
{
	if (weight > 1 || weight < 0) return;
	mRewardSpawnWeight = weight;
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
	auto player = PlayerManager::Get().GetPlayer();
	if (player) {
		player->AddScore(mScoreAwardAmt);
	}
	
}

void ly::EnemySpaceShip::SpawnReward()
{	
	if (!mRewardFactories.size()) return;
	if (RandomRange(0, 1) > mRewardSpawnWeight) return;
	int pick = (int) RandomRange(0, mRewardFactories.size());
	if (pick >= 0 && pick < mRewardFactories.size()) {
		auto reward = mRewardFactories[pick](GetWorld());
		reward.lock()->SetActorLocation(GetActorLocation());
	}
}
