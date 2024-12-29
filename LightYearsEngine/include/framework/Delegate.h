#pragma once 
#include <functional>
#include "framework/Core.h"

// A delegate is a class that wraps a pointer or reference to an object instance, 
// a member method of that object's class to be called on that object instance, 
// and provides a method to trigger that call.

namespace ly {
	class Object;

	template<typename... Args> 
	class Delegate {
	public:
		template<typename ClassName> 
		void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...)) {
			std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args) -> bool {
				if (!obj.expired()) {
					(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
					return true;
				}
				return false;
			};
			mCallbacks.emplace_back(callbackFunc);
		}

		void BroadCast(Args... args) {
			for (auto it = mCallbacks.begin(); it != mCallbacks.end();) {
				if ((*it)(args...)) {
					++it;
				}
				else it = mCallbacks.erase(it);
			}
		}

	private:
		List<std::function<bool(Args...)>> mCallbacks;
	};
};	