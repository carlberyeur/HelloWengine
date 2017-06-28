#include "stdafx.h"
#include "AlarmClock.h"

#include <thread>

namespace cu
{
	CAlarmClock::CAlarmClock()
		: myDoneTime(0.f)
	{
	}

	CAlarmClock::CAlarmClock(const Time aTimeTillRinging, const cu::CFunction<void>& aCallback)
		: CAlarmClock()
	{
		Init(aTimeTillRinging, aCallback);
	}

	CAlarmClock::~CAlarmClock()
	{
	}

	void CAlarmClock::Init(const Time aTimeTillRinging, const cu::CFunction<void>& aCallback)
	{
		myDoneTime = aTimeTillRinging;
		myCallback = aCallback;

		myStopWatch.Init();
	}

	void CAlarmClock::Update()
	{
		if (myCallback != nullptr)
		{
			myStopWatch.Update();
			if (myStopWatch.GetLifeTime() > myDoneTime)
			{
				if (myCallback)
				{
					myCallback();
					myCallback = nullptr;
					myStopWatch.Pause();
				}
			}
		}
	}
}
