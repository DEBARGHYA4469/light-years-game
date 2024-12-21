#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"

ly::Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
	: mWindow(sf::VideoMode(windowWidth, windowHeight), title, style),
	mTargetframeRate(60.f),
	mTickClock(),
	currentWorld(nullptr),
	mCleanCycleClock(),
	mCleanCycleInterval(2.f)
{
}

// game loop 
void ly::Application::run()
{	
	mTickClock.restart();
	float accumulatedTime = 0.f;
	float targetDeltaTime = 1.f / mTargetframeRate;

	while (mWindow.isOpen()) {
		sf::Event windowEvent;
		while (mWindow.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::EventType::Closed) {
				mWindow.close();
			}
		}
		accumulatedTime += mTickClock.restart().asSeconds();
		while (accumulatedTime > targetDeltaTime) {
			accumulatedTime -= targetDeltaTime;
			TickInternal(targetDeltaTime);
			RenderInternal();
		}
	}
}

sf::Vector2u ly::Application::GetWindowSize() const
{
	return mWindow.getSize();
}

void ly::Application::TickInternal(float DeltaTime)
{	

	Tick(DeltaTime);

	if (currentWorld) {
		currentWorld->BeginPlayInternal();
		currentWorld->tickInternal(DeltaTime);
	}

	// Tick aka Step the Physics System
	PhysicsSystem::Get().Step(DeltaTime);
		
	if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval) {
		mCleanCycleClock.restart();
		AssetManager::Get().CleanCycle();
		if (currentWorld) {
			currentWorld->CleanCycle();
		}
	}
}

void ly::Application::RenderInternal()
{
	mWindow.clear();

	Render();

	mWindow.display();
}

void ly::Application::Render()
{
	if (currentWorld) {
		currentWorld->Render(mWindow);
	}
}

void ly::Application::Tick(float DeltaTime)
{
	//LOG ("Ticking at Frame Rate: %f", 1.f / DeltaTime);
	//printf("Ticking at Frame Rate: %f" "\n" , 1.f / DeltaTime);
}
