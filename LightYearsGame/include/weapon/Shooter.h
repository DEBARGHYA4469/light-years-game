#pragma once 
#include "framework/Actor.h"

namespace ly {
	class Shooter {
	public:
		void Shoot(); 
		virtual bool CanShoot() const;
		virtual bool IsOnCoolDown() const;
		int GetCurrentLevel() const { return mCurrentLevel; }
		int GetMaxLevel() const { return mMaxLevel; }
		virtual void IncrementLevel(int Amt = 1);
		virtual void SetCurrentLevel(int Level) { mCurrentLevel = Level;  }
		Actor* GetOwner() const { return mOwner; }
	protected:
		Shooter(Actor* owner);
	private:
		int mCurrentLevel;
		int mMaxLevel;
		Actor* mOwner;
		virtual void ShootImpl() = 0; // abstract class
	};
};