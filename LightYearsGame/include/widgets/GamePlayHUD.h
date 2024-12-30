#pragma once 
#include <widgets/TextWidget.h>
#include <widgets/HUD.h>


namespace ly {
	class GamePlayHUD : public HUD {
	public:
		GamePlayHUD(); 
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float DeltaTime) override;
	private: 
		virtual void Init(const sf::RenderWindow& windowRef) override;
		TextWidget mFrameRateText;
	};
} 