#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

// Create a singleton timer manager class which holds only a unique timer objects

namespace ly {
    
	struct TimerHandle {
	public:
		TimerHandle();
		unsigned int GetTimerKey() const { return mTimerKey; }
	private:
		unsigned int mTimerKey;
		static unsigned int timerKeyCounter;
		unsigned int GetNextTimerKey() { return ++timerKeyCounter; }
	};

	struct TimerHandleHashFunction {
	public: 
		std::size_t operator()(const TimerHandle& handle) const {
			return handle.GetTimerKey();
		}
	};

	bool operator== (const TimerHandle& x, const TimerHandle& y);

	struct Timer {
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float Duration, bool repeat);
		void Tick(float DeltaTime);
		bool Expired() const;
		void SetExpired();
		std::pair<weak<Object>, std::function<void()>> listener;
	private:
		float mDuration;
		bool mRepeat;
		float mTimeCounter;
		bool mIsExpired;
	};

	class TimerManager {
	public:
		static TimerManager& Get();
		template <typename ClassName> 
		TimerHandle SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float Duration, bool repeat = false) {
			TimerHandle newHandle;
			mTimers.insert({ newHandle, Timer(weakRef, [=]() { (static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, Duration, repeat) });
			return newHandle;
		}
		void UpdateTimer(float DeltaTime);
		void ClearTimer(TimerHandle handle);
	protected:
		TimerManager();
	private:
		static unique<TimerManager> timerManager;
		Dictionary<TimerHandle, Timer, TimerHandleHashFunction> mTimers;
	};
};