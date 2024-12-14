#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

ly::World::World(Application* owningApp):
	mowningApp(owningApp),
	mBeganPlay(false),
	mActors{},
	mpendingActors{}
{
}

void ly::World::BeginPlayInternal()
{
	BeginPlay();
}

void ly::World::tickInternal(float deltaTime)
{
	for (shared<Actor> actor : mpendingActors) {
		mActors.push_back(actor);
		actor->BeginPlayInternal();
	}

	mpendingActors.clear();

	for (auto it = mActors.begin(); it != mActors.end();) {
		if (it->get()->isPendingDestroy()) {
			it = mActors.erase(it);
		}
		else {
			it->get()->TickInternal(deltaTime);
			it++;
		}
	}

	tick(deltaTime);
}

ly::World::~World()
{
}

void ly::World::tick(float deltaTime)
{
	LOG("Ticking at frame rate %f", 1.f / deltaTime);
}

void ly::World::BeginPlay()
{
	LOG("Begin Play ...");
}
