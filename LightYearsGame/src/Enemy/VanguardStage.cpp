#include "Enemy/VanguardStage.h"
#include "framework/World.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"

ly::VanguardStage::VanguardStage(World* world)
	: GameStage(world),
	mSpawnInterval(2.f), 
	mSwitchInterval(2.f),
	mSpawnDistanceToEdge(100.f),
	mLeftSpawnLocation{0.f, 0.f},
	mRightSpawnLocation{ 0.f, 0.f },
	mSpawnLocation{0.f, 0.f}, 
	mRowToSpawn{2}, 
	mCurrentRowVanguardCount{0},
	mVanguardPerRow{5},
	mRowSpawnCount{0}
{
}

void ly::VanguardStage::StartStage()
{
	auto windowSize = GetWorld()->getWindowSize();
	mLeftSpawnLocation = sf::Vector2f{ mSpawnDistanceToEdge, -100.f }; // vanguard's coming from outside
	mRightSpawnLocation = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100.f};
	SwitchRow();
}

void ly::VanguardStage::StageFinished()
{
	TimerManager::Get().ClearTimer(mSpawnTimerHandle);
	TimerManager::Get().ClearTimer(mSwitchTimerHandle);
}

void ly::VanguardStage::SpawnVanguard()
{
	//weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
	weak<TwinBlade> newVanguard = GetWorld()->SpawnActor<TwinBlade>();
	newVanguard.lock()->SetActorLocation(mSpawnLocation);
	+mCurrentRowVanguardCount++;
	if (mCurrentRowVanguardCount == mVanguardPerRow) {
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		mCurrentRowVanguardCount = 0;
		mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
	}
}

void ly::VanguardStage::SwitchRow()
{
	if (mRowSpawnCount == mRowToSpawn) {
		FinishStage();
		return;
	}
	if (mSpawnLocation == mLeftSpawnLocation) {
		mSpawnLocation = mRightSpawnLocation;
	}
	else mSpawnLocation = mLeftSpawnLocation;

	mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
	mRowSpawnCount++;
}
