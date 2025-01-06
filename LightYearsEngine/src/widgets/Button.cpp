#include "widgets/Button.h"
#include "framework/AssetManager.h"

ly::Button::Button(const std::string& textString, const std::string& buttonTexture):
	mTexture{ AssetManager::Get().LoadTexture(buttonTexture)},
	mSprite{*mTexture},
	mFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future_thin.ttf")},
	mText{textString, *mFont},
	mDefaultColor{128,128,128,255},
	mDownColor{64,64,64,255},
	mHoverColor{190, 190, 190, 255},
	mIsPressedDown{ false }
{
	mSprite.setColor(mDefaultColor);
	CenterText();
}

bool ly::Button::HandleEvent(const sf::Event& event)
{
	bool handled = false;
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (mSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				if (mIsPressedDown) {
					onButtonClicked.BroadCast();
					handled = true;
				}
			}
		}
		ButtonUp();
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (mSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				ButtonDown();
				handled = true;
			}
		}
	else if (event.type == sf::Event::MouseMoved) {
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (mSprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
					MouseHover();
					handled = true;
				}
				else {
					ButtonUp();
					handled = true;
				}
			}
	}
	return handled || Widget::HandleEvent(event);
}

void ly::Button::ButtonUp() {
	mIsPressedDown = false;
	mSprite.setColor(mDefaultColor);
}
void ly::Button::ButtonDown() {
	mIsPressedDown = true;
	mSprite.setColor(mDownColor);
}
void ly::Button::MouseHover() {
	mSprite.setColor(mHoverColor);
}

sf::FloatRect ly::Button::GetBound() const
{
	return mSprite.getGlobalBounds();
}

void ly::Button::Draw(sf::RenderWindow& windowRef)
{
	windowRef.draw(mSprite);
	windowRef.draw(mText);
}

void ly::Button::LocationUpdated(const sf::Vector2f& newLocation)
{
	mSprite.setPosition(newLocation);
	CenterText();
}

void ly::Button::RotationUpdated(float newRotation)
{
	mSprite.setRotation(newRotation);
	mText.setRotation(newRotation);
}

void ly::Button::CenterText() {
	sf::Vector2f widgetCenter = GetCenterPosition();
	sf::FloatRect textBound = mText.getGlobalBounds();
	mText.setPosition(widgetCenter - sf::Vector2f{ textBound.width / 2.f , textBound.height });
}

void  ly::Button::SetText(const std::string& newstr) {
	mText.setString(newstr);
	CenterText();
}

void ly::Button::SetTextSize(unsigned int charSize) {
	mText.setCharacterSize(charSize);
	CenterText();
}