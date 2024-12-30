#include "Enemy/UFOStage.h"
#include "Enemy/UFO.h"
#include "framework/MathUtil.h"
#include "framework/World.h"

ly::UFOStage::UFOStage(World* world)
	: GameStage(world),
	mSpawnAmount{4},
	mSpawnInterval{8.f},
	mUFOSpeed{200.f},
	mCurrentSpawnAmount{0}
{
}

void ly::UFOStage::StartStage()
{
	mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
}

void ly::UFOStage::TickStage(float DeltaTime)
{
}

sf::Vector2f ly::UFOStage::GetRandomSpawnLocation() const
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

void ly::UFOStage::StageFinished()
{
	TimerManager::Get().ClearTimer(mSpawnTimer);
}

void ly::UFOStage::SpawnUFO()
{
	auto windowSize = GetWorld()->GetWindowSize();
	sf::Vector2f center { windowSize.x / 2.f, windowSize.y / 2.f };
	sf::Vector2f spawnLocation = GetRandomSpawnLocation();
	sf::Vector2f SpawnLocationToCenter{ center - spawnLocation };
	Normalize(SpawnLocationToCenter);
	weak<UFO> ufo = GetWorld()->SpawnActor<UFO>(SpawnLocationToCenter * mUFOSpeed);
	ufo.lock()->SetActorLocation(spawnLocation);

	if (++mCurrentSpawnAmount == mSpawnAmount) {
		FinishStage();
	}
}
