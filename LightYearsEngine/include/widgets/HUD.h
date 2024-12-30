// Head Up display
#pragma once 
#include "framework/Object.h"
#include "SFML/Graphics.hpp"

namespace ly {
	class HUD : public Object {
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		bool HasInit() const { return mAlreadyInit;  }
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float DeltaTime);
	protected:
		HUD();
	private:
		// Template Method Pattern
		virtual void Init(const sf::RenderWindow& windowRef);
		bool mAlreadyInit;
	};
};