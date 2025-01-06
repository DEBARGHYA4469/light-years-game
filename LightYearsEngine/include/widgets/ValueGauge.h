#pragma once 
#include <widgets/Widget.h>

namespace ly {
	class ValueGauge : public Widget {
	public:
		ValueGauge(const sf::Vector2f& size = sf::Vector2f{ 320.f, 40.f }, 
			float initialPercent = .75f, 
			const sf::Color& FontBarColor = sf::Color{ 128, 255, 128, 255 }, 
			const sf::Color& BackBarColor = sf::Color{128, 128, 128, 255}
		);
		virtual bool HandleEvent(const sf::Event& event) override;
		virtual sf::FloatRect GetBound() const override { return mBarBackground.getGlobalBounds(); }
		void UpdateValue(float value, float maxValue);
		void SetForgroundColor(const sf::Color& C) { mBarFront.setFillColor(C); }
		void SetBackGroundColor(const sf::Color& C) { mBarBackground.setFillColor(C); }
		void SetTextSize(unsigned int charSize) { mText.setCharacterSize(charSize); }
		virtual ~ValueGauge();
	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);
		void CenterText();
		
		shared<sf::Font> mTextFont; 
		sf::Text mText; 

		sf::RectangleShape mBarFront; 
		sf::RectangleShape mBarBackground;
		sf::Color mBarForegroundColor;
		sf::Color mBarBackgroundColor;

		float mPercent;
	};
} 