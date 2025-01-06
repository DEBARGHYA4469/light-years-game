#include <widgets/ImageWidget.h>
#include <framework/AssetManager.h>

ly::ImageWidget::ImageWidget(const std::string& imagePath)
{
	mTexture = AssetManager::Get().LoadTexture(imagePath);
	mSprite = sf::Sprite{ *(mTexture.get()) };
}

bool ly::ImageWidget::HandleEvent(const sf::Event& event)
{
	return false;
}

sf::FloatRect ly::ImageWidget::GetBound() const
{
	return mSprite.getGlobalBounds();
}

void ly::ImageWidget::Draw(sf::RenderWindow& windowRef)
{
	windowRef.draw(mSprite);
}

void ly::ImageWidget::LocationUpdated(const sf::Vector2f& newLocation)
{
	mSprite.setPosition(newLocation);
}

void ly::ImageWidget::RotationUpdated(float newRotation)
{
	mSprite.setRotation(newRotation);
}
