#include "widgets/Widget.h"

void ly::WidgetBase::NativeDraw(sf::RenderWindow& windowRef)
{
	if (mIsVisible) {
		Draw(windowRef);
	}
}

bool ly::WidgetBase::HandleEvent(const sf::Event& event)
{
	return false;
}

void ly::WidgetBase::SetWidgetLocation(const sf::Vector2f& newLocation)
{
	mWidgetTransform.setPosition(newLocation);
	LocationUpdated(newLocation);
}

void ly::WidgetBase::SetWidgetRotation(float rotation)
{
	mWidgetTransform.setRotation(rotation);
	RotationUpdated(rotation);
}

void ly::WidgetBase::SetVisibility(bool newVisibiltiy)
{
	mIsVisible = newVisibiltiy;
}

ly::WidgetBase::WidgetBase() : mIsVisible(true), mWidgetTransform{}
{
}

void ly::WidgetBase::Draw(sf::RenderWindow& windowRef)
{
}

void ly::WidgetBase::LocationUpdated(const sf::Vector2f& newLocation)
{
}

void ly::WidgetBase::RotationUpdated(float newRotation)
{
}
