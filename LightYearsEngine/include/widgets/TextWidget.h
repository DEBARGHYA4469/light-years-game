#pragma once 
#include "framework/Core.h"
#include "widgets/Widget.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class TextWidget : public Widget {
	public:
		TextWidget(const std::string& textString, 
			const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future_thin.ttf",
			unsigned int charSize = 10);
		void SetText(const std::string& newString);
		void SetTextSize(unsigned int newSize);
		virtual sf::FloatRect GetBound() const override { return mText.getGlobalBounds(); }
	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;

		shared<sf::Font> mTextFont; // common for many objects
		sf::Text mText;
	};
}