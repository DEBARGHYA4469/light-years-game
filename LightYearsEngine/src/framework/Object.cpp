#include "framework/Object.h"
#include "framework/Core.h"

ly::Object::Object()
{
	mIsPendingDestroy = false;
}

ly::Object::~Object()
{
	LOG("Object Destroyed");
}

void ly::Object::Destroy()
{
	mIsPendingDestroy = true;
}
