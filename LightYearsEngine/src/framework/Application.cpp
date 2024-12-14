#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

ly::Application::Application() 
	: mWindow (sf::VideoMode(700, 700), "Light Years"),
	mTargetframeRate(60.f),
	mTickClock(),
	currentWorld(nullptr)
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

void ly::Application::TickInternal(float DeltaTime)
{	

	Tick(DeltaTime);

	if (currentWorld) {
		currentWorld->BeginPlayInternal();
		currentWorld->tickInternal(DeltaTime);
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
	sf::RectangleShape rect(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Green);
	rect.setOrigin(50, 50);
	rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
	mWindow.draw(rect);
}

void ly::Application::Tick(float DeltaTime)
{
	LOG ("Ticking at Frame Rate: %f", 1.f / DeltaTime);
	//printf("Ticking at Frame Rate: %f" "\n" , 1.f / DeltaTime);
}
