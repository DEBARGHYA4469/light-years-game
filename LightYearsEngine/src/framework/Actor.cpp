#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly {
	Actor::Actor(World* owningWorld, const std::string& texturePath) :
		mowningWorld(owningWorld),
		mHasBeganPlay(false)
	{
		this->setTexture(texturePath);
	}

	Actor::Actor(World* owningWorld)
	{
	}

	void Actor::BeginPlayInternal()
	{
		BeginPlay();
	}

	void Actor::TickInternal(float deltaTime)
	{	
		if (!isPendingDestroy()) {
			LOG("Actor ticking ...");
			Tick(deltaTime);
		}
	}

	void Actor::setTexture(const std::string& texturePath)
	{	
		AssetManager& assetManager = AssetManager::Get();
		mTexture = assetManager.LoadTexture(texturePath); // FlyWeights

		if (!mTexture) return;

		mSprite.setTexture(*mTexture);
		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(textureWidth, textureHeight)));
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (isPendingDestroy()) return;
		window.draw(mSprite);
	}

	Actor::~Actor() {
		LOG("Actor destroyed");
	}

	void Actor::BeginPlay()
	{
		LOG("Actor began Play!");
	}

	void Actor::Tick(float deltaTime)
	{
	}
}
