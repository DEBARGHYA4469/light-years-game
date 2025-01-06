#include "Enemy/ChaosStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/Hexagon.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/UFO.h"
#include "framework/World.h"

ly::ChaosStage::ChaosStage(World* world)
	: GameStage(world),
	mSpawnInterval(4.f),
	mMinSpawnInterval(0.5f),
	mSpawnIntervalDecrement{0.5f},
	mSpawnIntervalDecrementInterval{5.f},
	mStageDuration{60.f}
{

}

void ly::ChaosStage::StartStage()
{
	mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
	mDifficultTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, mSpawnIntervalDecrementInterval);
	TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
}

void ly::ChaosStage::TickStage(float DeltaTime)
{

}

void ly::ChaosStage::SpawnVanguard()
{
	weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
	newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
	newVanguard.lock()->SetActorRotation(90.f);
	mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
}
	

void ly::ChaosStage::SpawnTwinBlade()
{
	weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
	newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
	newTwinBlade.lock()->SetActorRotation(90.f);
	mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, mSpawnInterval);
}

void ly::ChaosStage::SpawnHexagon()
{
	weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
	newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
	newHexagon.lock()->SetActorRotation(90.f);
	mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
}

void ly::ChaosStage::SpawnUFO()
{
	weak<UFO> ufo = GetWorld()->SpawnActor<UFO>();
	sf::Vector2f spawnLocation = GetRandomSpawnLocationSide();
	auto windowSize = GetWorld()->GetWindowSize();
	sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
	sf::Vector2f SpawnLocationToCenter{ center - spawnLocation };
	Normalize(SpawnLocationToCenter);
	ufo.lock()->SetActorLocation(spawnLocation);
	ufo.lock()->SetVelocity(SpawnLocationToCenter * 200.f);
	ufo.lock()->SetActorRotation(90.f);
	mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
}

void ly::ChaosStage::IncreaseDifficulty()
{
	mSpawnInterval -= mSpawnIntervalDecrement;
	if (mSpawnInterval < mMinSpawnInterval) {
		mSpawnInterval = mMinSpawnInterval;
	}
}

void ly::ChaosStage::StageDurationReached()
{
	FinishStage();
}

sf::Vector2f ly::ChaosStage::GetRandomSpawnLocationTop() const
{
	auto windowSize = GetWorld()->GetWindowSize();
	float spawnX = RandomRange(100, windowSize.x - 100);
	float spawnY = -100.f;
	return sf::Vector2f(spawnX, spawnY);
}

sf::Vector2f ly::ChaosStage::GetRandomSpawnLocationSide() const
{
	
	auto windowSize = GetWorld()->GetWindowSize();
	float whichSide = RandomRange(-1, 1);

	float SpawnLocationX = 0;

	if (whichSide < 0) {
		SpawnLocationX = windowSize.x + 100.f;
	}
	else SpawnLocationX = -100.f;

	float SpawnLocationY = RandomRange(0, windowSize.y);
	return sf::Vector2f{ SpawnLocationX , SpawnLocationY };
}


void ly::ChaosStage::StageFinished()
{
	TimerManager::Get().ClearTimer(mDifficultTimerHandle);
	TimerManager::Get().ClearTimer(mSpawnTimer);
}