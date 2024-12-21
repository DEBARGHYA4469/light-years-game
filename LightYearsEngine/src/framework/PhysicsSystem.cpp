#include <box2D/b2_body.h>
#include <box2D/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>
#include <framework/PhysicsSystem.h>
#include <framework/Actor.h>
#include <framework/MathUtil.h>

namespace ly {
	unique<PhysicsSystem> PhysicsSystem::physicsSystem = nullptr; // to avoid link error! 

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (physicsSystem == nullptr) {
			physicsSystem = std::move(unique<PhysicsSystem> {new PhysicsSystem });
		}
		return *physicsSystem;
	}

	void PhysicsSystem::Step(float DeltaTime)
	{	
		ProcessPendingRemoveListener();
		mPhysicsWorld.Step(DeltaTime, mVelocityIteration, mPositionIteration);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->isPendingDestroy()) return nullptr;
		
		// Create the physics body definition, builder + prototype
		b2BodyDef bodyDef; 
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t> (listener); // just to store the pointer address. 
		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreeToRadians(listener->GetActorRotation());

		// Create the physics Body 
		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef); // actual physics body instance
		b2PolygonShape shape; 
		auto bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width/2.f * GetPhysicsScale(), bound.height/2.f * GetPhysicsScale()); // half size
		
		// Physics Body Fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.f;
		fixtureDef.friction = .3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);
		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* body)
	{
		mPendingRemoveListener.emplace(body);
	}

	void PhysicsSystem::CleanUp()
	{
		physicsSystem = std::move(unique<PhysicsSystem> {new PhysicsSystem });
	}

	// private
	PhysicsSystem::PhysicsSystem() :
		mPhysicsWorld(b2Vec2{0.f, 0.f}),
		mPhysicsScale(0.01f),
		mVelocityIteration(8),
		mPositionIteration(3),
		mContactListener{},
		mPendingRemoveListener{}
	{
		mPhysicsWorld.SetContactListener(&mContactListener);
		mPhysicsWorld.SetAllowSleeping(false); // fire it even when the step function is not called.
	}

	void PhysicsSystem::ProcessPendingRemoveListener()
	{
		for (auto listener : mPendingRemoveListener) {
			mPhysicsWorld.DestroyBody(listener);
		}
		mPendingRemoveListener.clear();
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact) {
		Actor* actorA = reinterpret_cast<Actor*> (contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* actorB = reinterpret_cast<Actor*> (contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		
		if (actorA && !actorA->isPendingDestroy()) {
			actorA->OnActorBeginOverlap(actorB);
		}

		if (actorB && !actorB->isPendingDestroy()) {
			actorB->OnActorBeginOverlap(actorA);
		}
	}
	void PhysicsContactListener::EndContact(b2Contact* contact){
		Actor* actorA = nullptr;
		Actor* actorB = nullptr;
		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody()) {
			actorA = reinterpret_cast<Actor*> (contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}
		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody()) {
			actorB = reinterpret_cast<Actor*> (contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}
		if (actorA && !actorA->isPendingDestroy()) {
			actorA->OnActorEndOverlap(actorB);
		}
		if (actorB && !actorB->isPendingDestroy()) {
			actorB->OnActorEndOverlap(actorA);
		}
	}
};
