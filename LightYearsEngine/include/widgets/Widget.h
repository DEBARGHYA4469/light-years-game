#pragma once 
#include <framework/Object.h>
#include <SFML/Graphics.hpp>

namespace ly {
	class Widget : public Object {
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);
		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float rotation);
		sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
		float GetWidgetRotation() const { return mWidgetTransform.getRotation(); }
		void SetVisibility(bool newVisibiltiy);
		bool GetVisibility() const { return mIsVisible; }
		virtual sf::FloatRect GetBound() const = 0;
		virtual sf::Vector2f GetCenterPosition() const;
	protected:
		Widget();
		virtual ~Widget();
	private:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);
		sf::Transformable mWidgetTransform;
		bool mIsVisible;
	};
};