#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/World.h"

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
			//LOG("Actor ticking ...");
			Tick(deltaTime);
		}
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
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
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (isPendingDestroy()) return;
		window.draw(mSprite);
	}

	void Actor::setActorLocation(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}

	void Actor::setActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		this->setActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(const float offsetAmt)
	{
		this->setActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mowningWorld->getWindowSize();
	}

	Actor::~Actor() {
		//LOG("Actor destroyed");
	}

	void Actor::BeginPlay()
	{
		//LOG("Actor began Play!");
	}

	void Actor::Tick(float deltaTime)
	{
	}
}
