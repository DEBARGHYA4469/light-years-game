#pragma once 
#include <widgets/Widget.h>
#include <SFML/Graphics.hpp>

namespace ly {
	class ImageWidget : public Widget {
	public:
		ImageWidget(const std::string& imagePath);
		void SetImage(const shared<sf::Texture>& texture) {
			if (texture) { mTexture = texture; mSprite.setTexture(*texture); }
		}
	private:
		shared<sf::Texture> mTexture;
		sf::Sprite mSprite;
	public:
		virtual bool HandleEvent(const sf::Event& event);
		virtual sf::FloatRect GetBound() const;
	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);
	};
};