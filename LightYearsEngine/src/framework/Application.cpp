#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

ly::Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
	: mWindow(sf::VideoMode(windowWidth, windowHeight), title, style),
	mTargetframeRate(60.f),
	mTickClock(),
	mcurrentWorld(nullptr),
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

	if(mcurrentWorld) mcurrentWorld->BeginPlayInternal();

	while (mWindow.isOpen()) {
		sf::Event windowEvent;
		while (mWindow.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::EventType::Closed) {
				QuitApplication();
			}
			else {
				DispatchEvent(windowEvent);
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

bool ly::Application::DispatchEvent(const sf::Event& event)
{
	if (mcurrentWorld) {
		mcurrentWorld->DispatchEvent(event);
	}
	return true;
}

void ly::Application::TickInternal(float DeltaTime)
{	

	Tick(DeltaTime);

	if (mcurrentWorld) {
		mcurrentWorld->tickInternal(DeltaTime);
	}

	// Step the timer 
	TimerManager::Get().UpdateTimer(DeltaTime);

	// Tick aka Step the Physics System
	PhysicsSystem::Get().Step(DeltaTime);
		
	if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval) {
		mCleanCycleClock.restart();
		AssetManager::Get().CleanCycle();
		if (mcurrentWorld) {
			mcurrentWorld->CleanCycle();
		}
	}

	if (mPendingWorld && mPendingWorld != mcurrentWorld) {
		mcurrentWorld = mPendingWorld;
		mcurrentWorld->BeginPlayInternal();
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
	if (mcurrentWorld) {
		mcurrentWorld->Render(mWindow);
	}
}

void ly::Application::Tick(float DeltaTime)
{
	//LOG ("Ticking at Frame Rate: %f", 1.f / DeltaTime);
	//printf("Ticking at Frame Rate: %f" "\n" , 1.f / DeltaTime);
}

void ly::Application::QuitApplication() {
	mWindow.close();
}