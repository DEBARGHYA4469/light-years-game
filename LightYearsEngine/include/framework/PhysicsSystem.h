#pragma once
#include <framework/Core.h>
#include <box2d/b2_world.h>

namespace ly {

	class PhysicsContactListener : public b2ContactListener {
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class Actor;
	class PhysicsSystem {
	public: 
		static PhysicsSystem& Get();
		void Step(float DeltaTime); // same as tick 
		b2Body* AddListener(Actor* listener); // observer pattern
		void RemoveListener(b2Body* body);
		float GetPhysicsScale() const { return mPhysicsScale; }
		static void CleanUp();
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> physicsSystem; 
		b2World mPhysicsWorld; // Box2D physics instance 
		float mPhysicsScale;
		float mVelocityIteration;
		float mPositionIteration;
		PhysicsContactListener mContactListener;
		Set<b2Body*> mPendingRemoveListener;
		void ProcessPendingRemoveListener();
	};
};