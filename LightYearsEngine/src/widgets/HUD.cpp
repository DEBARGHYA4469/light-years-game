#include "widgets/HUD.h"

void ly::HUD::NativeInit(const sf::RenderWindow& windowRef)
{
	if (!mAlreadyInit) {
		mAlreadyInit = true;
		Init(windowRef);
	}
}

bool ly::HUD::HandleEvent(const sf::Event& event)
{
	return false;
}

void ly::HUD::Tick(float DeltaTime)
{
}

ly::HUD::HUD() : mAlreadyInit(false)
{
}

void ly::HUD::Init(const sf::RenderWindow& windowRef)
{
}
