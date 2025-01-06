#pragma once 
#include <widgets/TextWidget.h>
#include <widgets/HUD.h>
#include <framework/Actor.h>
#include <widgets/ValueGauge.h>
#include <widgets/ImageWidget.h>
#include <widgets/Button.h>

namespace ly {
	class GamePlayHUD : public HUD {
	public:
		GamePlayHUD(); 
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float DeltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;
	private: 
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void RefreshHealthBar();
		void RefreshPlayerLifeCount();
		void RefreshPlayerScore();
		TextWidget mFrameRateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeCountText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHLBColor;
		sf::Color mWarningHLBColor;
		sf::Color mCriticalHLBColor;
		float mCriticalThreshold;
		float mWidgetSpacing;

		void PlayerHealthUpdated(float, float, float);
		void PlayerSpaceShipDestroyed(Actor* actor);
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int Score);
	};
} 