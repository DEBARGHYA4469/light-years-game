#pragma once 
#include <memory>
#include <framework/Core.h>
#include <framework/Delegate.h>

namespace ly {
	// give out a weak pointer of self
	class Object : public std::enable_shared_from_this<Object> { // abstract class,
	public:
		Object(); 
		virtual ~Object();
		virtual void Destroy();
		bool isPendingDestroy() const { return mIsPendingDestroy; }

		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;
		Delegate<Object*> OnDestroy; 

	private:
		bool mIsPendingDestroy;
	};
};