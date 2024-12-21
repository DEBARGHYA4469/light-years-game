#pragma once 
#include "framework/Actor.h"

namespace ly {
	class Shooter {
	public:
		void Shoot(); 
		virtual bool CanShoot() const;
		virtual bool IsOnCoolDown() const;
		Actor* GetOwner() const { return mOwner; }
	protected:
		Shooter(Actor* owner);
	private:
		Actor* mOwner;
		virtual void ShootImpl() = 0; // abstract class
	};
};