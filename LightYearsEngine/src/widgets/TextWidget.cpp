#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

ly::TextWidget::TextWidget(const std::string& textString, const std::string& fontPath, unsigned int charSize):
	mTextFont{ AssetManager::Get().LoadFont (fontPath) },
	mText { textString, *(mTextFont.get()), charSize }
{

}

void ly::TextWidget::SetText(const std::string& newString)
{
	mText.setString(newString);
}

void ly::TextWidget::SetTextSize(unsigned int newSize)
{
	mText.setCharacterSize(newSize);
}

void ly::TextWidget::Draw(sf::RenderWindow& windowRef)
{
	windowRef.draw(mText);
}

void ly::TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
{
	mText.setPosition(newLocation);
}

void ly::TextWidget::RotationUpdated(float newRotation)
{
	mText.setRotation(newRotation);
}
