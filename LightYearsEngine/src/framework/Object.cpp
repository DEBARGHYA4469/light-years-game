#include "framework/Object.h"
#include "framework/Core.h"

ly::Object::Object()
{
	mIsPendingDestroy = false;
	mUniqueID = GetNextAvailableID();
}

ly::Object::~Object()
{
	LOG("Object Destroyed");
	OnDestroy.BroadCast(this);
}

void ly::Object::Destroy()
{
	mIsPendingDestroy = true;
}

ly::weak<ly::Object> ly::Object::GetWeakRef() // Get weak reference of self
{
	return weak_from_this();
}
 
ly::weak<const ly::Object> ly::Object::GetWeakRef() const // Get weak reference of self
{
	return weak_from_this();
}

unsigned int ly::Object::uniqueIDCounter = 0;

unsigned int ly::Object::GetNextAvailableID()
{
	return ++uniqueIDCounter;
}
