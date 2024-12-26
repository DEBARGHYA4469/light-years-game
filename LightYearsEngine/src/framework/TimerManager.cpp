#include "framework/TimerManager.h"
#include "framework/Core.h"

namespace ly {
	unique<TimerManager> TimerManager::timerManager{ nullptr };

	TimerManager& TimerManager::Get()
	{
		if (timerManager == nullptr) {
			timerManager = std::move(unique<TimerManager>(new TimerManager));
		}
		return *timerManager;
	}

	void TimerManager::UpdateTimer(float DeltaTime)
	{	
		for (auto it = mTimers.begin(); it != mTimers.end();) {
			if (it->second.Expired()) {
				it = mTimers.erase(it);
			}
			else {
				it->second.Tick(DeltaTime);
				it++;
			}
		}
	}

	// Requires a Default Constructor for Timer
	// Because map requires DefaultConstructible values, since when using subscript operator and the key is not found it adds it mapped to a default constructed value.
	void TimerManager::ClearTimer(TimerHandle handle)
	{
		if (mTimers.find(handle) != mTimers.end())
			mTimers.at(handle).SetExpired();
	}

	TimerManager::TimerManager()
	{
	}


	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float Duration, bool repeat):
		listener{weakRef, callback}, mDuration(Duration), mRepeat(repeat), mTimeCounter(0.f), mIsExpired(false)
	{

	}

	void Timer::Tick(float DeltaTime)
	{
		if (Expired()) return;
		mTimeCounter += DeltaTime;
		
		if (mTimeCounter >= mDuration) {
			listener.second();
			if (mRepeat) {
				mTimeCounter = 0.f;
			}
			else SetExpired();
		}
	}

	bool Timer::Expired() const
	{
		return mIsExpired || listener.first.expired() || listener.first.lock()->isPendingDestroy();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	unsigned int TimerHandle::timerKeyCounter = 0;

	TimerHandle::TimerHandle() : mTimerKey(GetNextTimerKey()) {

	}

	bool operator== (const TimerHandle& lhs, const TimerHandle& rhs) {
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}
};

