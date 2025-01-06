#pragma once 
#include <widgets/Widget.h>
#include <framework/Delegate.h>

namespace ly {
	class Button : public Widget {
	private:
		shared<sf::Texture> mTexture;
		sf::Sprite mSprite;
		shared<sf::Font> mFont;
		sf::Text mText;

		sf::Color mDefaultColor;
		sf::Color mDownColor;
		sf::Color mHoverColor;
		bool mIsPressedDown;

	public:
		Button(const std::string& textString = "Button", 
			const std::string& buttonTexture = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
		void SetText(const std::string& newstr);
		void SetTextSize(unsigned int charSize);
		virtual bool HandleEvent(const sf::Event& event);
		virtual sf::FloatRect GetBound() const override;
		Delegate<> onButtonClicked;
	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);
		void ButtonUp();
		void ButtonDown();
		void MouseHover();
		void CenterText();

	};
};