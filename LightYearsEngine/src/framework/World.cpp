#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

ly::World::World(Application* owningApp):
	mowningApp(owningApp),
	mBeganPlay(false),
	mActors{},
	mPendingActors{},
	mCurrentStageIndex{-1},
	mGameStages{}
{
}

void ly::World::BeginPlayInternal()
{
	if (!mBeganPlay) {
		mBeganPlay = true;
		BeginPlay();
		InitGameStages();
		NextGameStage();
	}
}

void ly::World::tickInternal(float deltaTime)
{
	for (shared<Actor> actor : mPendingActors) {
		mActors.push_back(actor);
		actor->BeginPlayInternal();
	}

	mPendingActors.clear();

	for (auto it = mActors.begin(); it != mActors.end();) {
		it->get()->TickInternal(deltaTime);
		it++;
	}

	if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size()) {
		mGameStages[mCurrentStageIndex]->TickStage(deltaTime);
	}

	tick(deltaTime);
}

void ly::World::Render(sf::RenderWindow& window)
{
	for (auto actor : mActors) {
		actor->Render(window);
	}
}

ly::World::~World()
{
}

sf::Vector2u ly::World::getWindowSize() const
{
	return mowningApp->GetWindowSize();
}

void ly::World::CleanCycle()
{
	for (auto it = mActors.begin(); it != mActors.end();) {
		if (it->get()->isPendingDestroy()) {
			it = mActors.erase(it);
		}
		else {
			it++;
		}
	}

	for (auto it = mGameStages.begin(); it != mGameStages.end();) {
		if (it->get()->IsStageFinished()) {
			it = mGameStages.erase(it);
		}
		else {
			it++;
		}
	}
}

void ly::World::AddGameStage(const shared<GameStage>& newStage)
{
	mGameStages.push_back(newStage);
}

void ly::World::tick(float deltaTime)
{
	//LOG("Ticking at frame rate %f", 1.f / deltaTime);
}

void ly::World::BeginPlay()
{
	//LOG("Begin Play ...");
}

void ly::World::InitGameStages()
{

}


void ly::World::NextGameStage()
{
	++mCurrentStageIndex;
	if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size()) {
		mGameStages[mCurrentStageIndex]->OnStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		mGameStages[mCurrentStageIndex]->StartStage();
	}
	else {
		AllGameStagesFinished();
	}
}

void ly::World::AllGameStagesFinished()
{
	LOG("All game stages finished");
}
