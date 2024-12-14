#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly {
	Actor::Actor(World* owningWorld) :
		mowningWorld(owningWorld),
		mHasBeganPlay(false)
	{

	}

	void Actor::BeginPlayInternal()
	{
		BeginPlay();
	}

	void Actor::TickInternal(float deltaTime)
	{	
		LOG("Actor ticking ...");
		Tick(deltaTime);
	}

	Actor::~Actor() {
		LOG("Actor destroyed");
	}

	void Actor::BeginPlay()
	{
		LOG("Actor began Play!");
	}

	void Actor::Tick(float deltaTime)
	{
	}
}
