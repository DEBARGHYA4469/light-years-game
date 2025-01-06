#pragma once 
#include <widgets/HUD.h>
#include <widgets/Button.h>
#include <widgets/TextWidget.h>

namespace ly {
	class MainMenuHUD : public HUD {
	public:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float DeltaTime);
		Delegate<> onStartButtonClicked;
		Delegate<> onQuitButtonClicked;
	public:
		MainMenuHUD();
	private:
		// Template Method Pattern
		virtual void Init(const sf::RenderWindow& windowRef);
		Button mStartBtn;
		Button mQuitBtn;
		TextWidget mTitleText;
		
		void StartButtonClicked();
		void QuitButtonClicked();
	};
};