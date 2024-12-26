#include "gameplay/GameStage.h"
#include "framework/Core.h"

ly::GameStage::GameStage(World* world): mWorld(world), mStageFinished(false)
{

}

void ly::GameStage::StartStage()
{
	//LOG("Stage Started");
}

void ly::GameStage::TickStage(float DeltaTime)
{
	//LOG("Stage Ticked");
}

void ly::GameStage::FinishStage()
{
	OnStageFinished.BroadCast();
	mStageFinished = true;
	StageFinished();
}

void ly::GameStage::StageFinished()
{
	//LOG("Stage Finished");
}
