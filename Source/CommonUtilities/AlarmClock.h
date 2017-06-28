#pragma once

#include "CUTime.h"
#include "StopWatch.h"

namespace cu
{
	class CAlarmClock
	{
	public:
		CAlarmClock();
		CAlarmClock(const Time aTimeTillRinging, const cu::CFunction<void>& aCallback);
		~CAlarmClock();

		void Init(const Time aTimeTillRinging, const cu::CFunction<void>& aCallback);
		void Update();

	private:
		cu::CFunction<void> myCallback;
		CStopWatch myStopWatch;
		Time myDoneTime;
	};
}
