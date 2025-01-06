#include "widgets/Widget.h"

void ly::Widget::NativeDraw(sf::RenderWindow& windowRef)
{
	if (mIsVisible) {
		Draw(windowRef);
	}
}

bool ly::Widget::HandleEvent(const sf::Event& event)
{
	return false;
}

void ly::Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
{
	mWidgetTransform.setPosition(newLocation);
	LocationUpdated(newLocation);
}

void ly::Widget::SetWidgetRotation(float rotation)
{
	mWidgetTransform.setRotation(rotation);
	RotationUpdated(rotation);
}

void ly::Widget::SetVisibility(bool newVisibiltiy)
{
	mIsVisible = newVisibiltiy;
}

ly::Widget::Widget() : mIsVisible(true), mWidgetTransform{}
{
}

void ly::Widget::Draw(sf::RenderWindow& windowRef)
{
}

void ly::Widget::LocationUpdated(const sf::Vector2f& newLocation)
{
}

void ly::Widget::RotationUpdated(float newRotation)
{
}

sf::Vector2f ly::Widget::GetCenterPosition() const{
	sf::FloatRect bound = GetBound();
	return sf::Vector2f{ bound.left + bound.width / 2.f, bound.top + bound.height / 2.f};
}
ly::Widget::~Widget() {

}