#include <widgets/MainMenuHUD.h>

void ly::MainMenuHUD::Draw(sf::RenderWindow& windowRef)
{
	mTitleText.NativeDraw(windowRef);
	mStartBtn.NativeDraw(windowRef);
	mQuitBtn.NativeDraw(windowRef);
}

bool ly::MainMenuHUD::HandleEvent(const sf::Event& event)
{
	return mStartBtn.HandleEvent(event) || mQuitBtn.HandleEvent(event);
}

void ly::MainMenuHUD::Tick(float DeltaTime)
{
}

ly::MainMenuHUD::MainMenuHUD():
	mTitleText{"Light Years"},
	mStartBtn{"Start"},
	mQuitBtn{"Quit"}
{
	mTitleText.SetTextSize(60);
	mStartBtn.SetTextSize(40);
	mQuitBtn.SetTextSize(40);
}

void ly::MainMenuHUD::Init(const sf::RenderWindow& windowRef)
{
	sf::Vector2u windowSize = windowRef.getSize();

	mTitleText.SetWidgetLocation(sf::Vector2f{ windowSize.x / 2.f, 100.f } - sf::Vector2f{mTitleText.GetBound().width /2.f, 0});
	mStartBtn.SetWidgetLocation(sf::Vector2f{ windowSize.x / 2.f, windowSize.y / 2.f } - sf::Vector2f{ mStartBtn.GetBound().width / 2.f, 0 });
	mQuitBtn.SetWidgetLocation(sf::Vector2f{ windowSize.x / 2.f, windowSize.y / 2.f } + sf::Vector2f{0.f, 50.f} - sf::Vector2f{ mQuitBtn.GetBound().width / 2.f, 0 });

	mStartBtn.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
	mQuitBtn.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
}

void ly::MainMenuHUD::StartButtonClicked()
{
	onStartButtonClicked.BroadCast();
}

void ly::MainMenuHUD::QuitButtonClicked()
{
	onQuitButtonClicked.BroadCast();
}
