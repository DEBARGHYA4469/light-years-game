#include "widgets/GamePlayHUD.h"

ly::GamePlayHUD::GamePlayHUD(): mFrameRateText("Frame Rate: ")
{
	mFrameRateText.SetTextSize(40);
}

void ly::GamePlayHUD::Draw(sf::RenderWindow& windowRef)
{
	mFrameRateText.NativeDraw(windowRef);
}

void ly::GamePlayHUD::Tick(float DeltaTime)
{
	int frameRate = int (1.f / DeltaTime);
	std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
	mFrameRateText.SetText(frameRateStr);
}

void ly::GamePlayHUD::Init(const sf::RenderWindow& windowRef)
{
}
