#include "framework/Actor.h"
#include "framework/MathUtil.h"
#include "player/PlayerManager.h"
#include "player/Player.h"
#include "player/PlayerSpaceShip.h"
#include "SFML/Graphics.hpp"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"
#include "widgets/GamePlayHUD.h"

ly::GamePlayHUD::GamePlayHUD() : 
	mFrameRateText("Frame Rate: "), 
	mPlayerHealthBar{}, 
	mPlayerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" }, 
	mPlayerLifeCountText{"3"},
	mPlayerScoreIcon{"SpaceShooterRedux/PNG/Power-ups/star_gold.png"},
	mPlayerScoreText{"0"}
{
	mFrameRateText.SetTextSize(40);
	mPlayerLifeCountText.SetTextSize(30);

	mCriticalHLBColor = sf::Color::Red;
	mHealthyHLBColor = sf::Color::Green;
	mWarningHLBColor = sf::Color::Yellow;
	mCriticalThreshold = 0.3f;
	mWidgetSpacing = 10.f;

	mPlayerScoreText.SetTextSize(30);
}

void ly::GamePlayHUD::Draw(sf::RenderWindow& windowRef)
{
	List<Widget*> HUDwidgets = { &mFrameRateText, &mPlayerHealthBar, &mPlayerLifeIcon , 
		&mPlayerLifeCountText, &mPlayerScoreIcon, &mPlayerScoreText};

	for (auto wptr : HUDwidgets)
		wptr->NativeDraw(windowRef);
}

void ly::GamePlayHUD::Tick(float DeltaTime)
{
	int frameRate = int (1.f / DeltaTime);
	std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
	mFrameRateText.SetText(frameRateStr);
}

bool ly::GamePlayHUD::HandleEvent(const sf::Event& event)
{
	return HUD::HandleEvent(event); // chain of responsiblity
}

void ly::GamePlayHUD::Init(const sf::RenderWindow& windowRef)
{
	auto windowSize = windowRef.getSize();
	mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{0.f, windowSize .y - 50.f});
	mPlayerHealthBar.SetWidgetRotation(0.f);
	mPlayerHealthBar.UpdateValue (100, 200.f);

	RefreshHealthBar();
	RefreshPlayerLifeCount();
	RefreshPlayerScore();

	// Set location of Player Life Icon
	sf::Vector2f nextWidgetPosition = mPlayerHealthBar.GetWidgetLocation();
	nextWidgetPosition += sf::Vector2f { mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0 };
	mPlayerLifeIcon.SetWidgetLocation(nextWidgetPosition);
	
	nextWidgetPosition += sf::Vector2f { mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0 };
	mPlayerLifeCountText.SetWidgetLocation(nextWidgetPosition);

	nextWidgetPosition += sf::Vector2f {mPlayerLifeCountText.GetBound().width + mWidgetSpacing * 4, 0};
	mPlayerScoreIcon.SetWidgetLocation(nextWidgetPosition);

	nextWidgetPosition += sf::Vector2f { mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0 };
	mPlayerScoreText.SetWidgetLocation (nextWidgetPosition);
}

void ly::GamePlayHUD::RefreshHealthBar()
{
	Player* player = PlayerManager::Get().GetPlayer();
	if (player && !player->GetCurrentSpaceShip().expired()) {
		weak<PlayerSpaceShip> playerSpaceShip = player->GetCurrentSpaceShip();
		playerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GamePlayHUD::PlayerSpaceShipDestroyed);
		auto& health = playerSpaceShip.lock()->GetHealthComponent();
		health.OnHealthChanged.BindAction(GetWeakRef(), &GamePlayHUD::PlayerHealthUpdated);
		PlayerHealthUpdated(0, health.GetHealth(), health.GetMaxHealth());
	}
}


void ly::GamePlayHUD::PlayerHealthUpdated(float amt, float currhealth, float maxhealth)
{
	mPlayerHealthBar.UpdateValue(currhealth, maxhealth);
	float mPercent = currhealth / maxhealth;
	if (mPercent > 0.5) mPlayerHealthBar.SetForgroundColor(mHealthyHLBColor);
	else if (mPercent < mCriticalThreshold) mPlayerHealthBar.SetForgroundColor(mCriticalHLBColor);
	else mPlayerHealthBar.SetForgroundColor(mWarningHLBColor);
}

void ly::GamePlayHUD::PlayerSpaceShipDestroyed(Actor* actor)
{
	RefreshHealthBar();
}

void ly::GamePlayHUD::PlayerLifeCountUpdated(int amt)
{
	mPlayerLifeCountText.SetText(std::to_string(amt));
}

void ly::GamePlayHUD::RefreshPlayerLifeCount()
{
	Player* player = PlayerManager::Get().GetPlayer();
	if (player) {
		int lifeCount = player->GetLifeCount();
		mPlayerLifeCountText.SetText(std::to_string(lifeCount));
		player->onLifeChanged.BindAction(GetWeakRef(), &GamePlayHUD::PlayerLifeCountUpdated);
	}
}

void ly::GamePlayHUD::RefreshPlayerScore()
{
	Player* player = PlayerManager::Get().GetPlayer();
	if (player) {
		player->onScoreChanged.BindAction(GetWeakRef(), &GamePlayHUD::PlayerScoreUpdated);
	}
}

void ly::GamePlayHUD::PlayerScoreUpdated(int Score)
{
	mPlayerScoreText.SetText(std::to_string(Score));
}
 