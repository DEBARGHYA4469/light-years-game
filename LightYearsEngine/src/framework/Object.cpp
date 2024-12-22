#include "framework/Object.h"
#include "framework/Core.h"

ly::Object::Object()
{
	mIsPendingDestroy = false;
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
