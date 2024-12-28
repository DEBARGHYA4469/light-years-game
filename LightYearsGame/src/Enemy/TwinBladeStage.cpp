#include "Enemy/TwinBlade.h"
#include "Enemy/TwinBladeStage.h"
#include "framework/World.h"

ly::TwinBladeStage::TwinBladeStage(World* world): GameStage(world),
	mSpawnInterval(1.5),
	mSpawnDistanceToCenter(100.f), 
	mLeftSpawnLocation(world->getWindowSize().x / 2.f - mSpawnDistanceToCenter, -100.f),
	mRightSpawnLocation(world->getWindowSize().x / 2.f  + mSpawnDistanceToCenter, -100.f),
	mSpawnLocation(mLeftSpawnLocation),
	mSpawnAmount(10),
	mCurrentSpawnCount(0)

{
}

void ly::TwinBladeStage::StartStage()
{
	mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
}


void ly::TwinBladeStage::SpawnTwinBlade()
{
	weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
	newTwinBlade.lock()->SetActorLocation(mSpawnLocation);
	if (mSpawnLocation == mLeftSpawnLocation) mSpawnLocation = mRightSpawnLocation;
	else mSpawnLocation = mLeftSpawnLocation;
	++mCurrentSpawnCount;
	if (mCurrentSpawnCount == mSpawnAmount) {
		mCurrentSpawnCount = 0;
		FinishStage();
	}
}

void ly::TwinBladeStage::StageFinished()
{
	TimerManager::Get().ClearTimer(mSpawnTimerHandle);
}
