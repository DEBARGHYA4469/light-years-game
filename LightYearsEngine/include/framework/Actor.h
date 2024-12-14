#pragma once 

#include "framework/Object.h"

namespace ly {
	class World;
	class Actor : public Object{
	private:
		World* mowningWorld;
		bool mHasBeganPlay;
	public:
		Actor(World* owningWorld);
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
	};
}