#pragma once 

namespace ly {
	class Object { // abstract class 
	public:
		Object();
		virtual ~Object() = 0;
		void Destroy();
		bool isPendingDestroy() const { return mIsPendingDestroy; }
	private:
		bool mIsPendingDestroy;
	};
};