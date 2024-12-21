#include "box2d/b2_body.h"
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly {
	Actor::Actor(World* owningWorld, const std::string& texturePath) :
		mowningWorld(owningWorld),
		mHasBeganPlay(false),
		mSprite{},
		mTexture{},
		mPhysicsBody{nullptr},
		mEnablePhysics{false}
	{
		setTexture(texturePath);
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
		UpdatePhysicsBodyTransform();
	}

	void Actor::setActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
		UpdatePhysicsBodyTransform();
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
		return RotationToVector(GetActorRotation() - 90.f);
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mowningWorld->getWindowSize();
	}

	Actor::~Actor() {
		//LOG("Actor destroyed");
	}

	bool Actor::IsActorOutOfWindowBounds() const
	{	
		float windowWidth = GetWorld()->getWindowSize().x;
		float windowHeight = GetWorld()->getWindowSize().y; 
		
		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();
		if (actorPos.x < -width) return true;
		if (actorPos.y < -height) return true;
		if (actorPos.x > windowWidth + width) return true; // right 
		if (actorPos.y > windowHeight + height) return true; // down 
		return false;
	}

	void Actor::BeginPlay()
	{
		//LOG("Actor began Play!");
	}

	void Actor::Tick(float deltaTime)
	{
		// LOG("Actor Ticking ...");
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		mEnablePhysics = enable;
		if (mEnablePhysics) {
			InitializePhysics();
		}
		else {
			UnInitializePhysics();
		}
	}

	void Actor::InitializePhysics()
	{
		if (!mPhysicsBody) {
			mPhysicsBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UnInitializePhysics()
	{
		if (mPhysicsBody) {
			PhysicsSystem::Get().RemoveListener(mPhysicsBody);
			mPhysicsBody = nullptr;
		}
	}
	
	void Actor::UpdatePhysicsBodyTransform()
	{
		if (mPhysicsBody) {
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreeToRadians(GetActorRotation());
			mPhysicsBody->SetTransform(pos, rotation);
		}
	}
	void Actor::OnActorBeginOverlap(Actor* actor)
	{
		LOG("Overlapped");
	}
	void Actor::OnActorEndOverlap(Actor* actor)
	{
		LOG("Overlapped finished");
	}
	void Actor::Destroy()
	{	
		UnInitializePhysics();
		Object::Destroy();
	}
}
