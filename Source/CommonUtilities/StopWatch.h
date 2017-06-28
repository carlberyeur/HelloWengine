#pragma once

#include "CUTime.h"
#include <chrono>

namespace cu
{
	class CStopWatch
	{
	public:
		CStopWatch();
		~CStopWatch();

		void Init();
		void Start();
		void Restart();
		void Pause();
		void Stop();
		void Update();

		inline Time GetLifeTime() const;
		inline Time GetDeltaTime() const;

	private:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		using MicroSeconds = std::chrono::microseconds;
		using FloatDuration = std::chrono::duration<float>;

		TimePoint myLastTimePoint;

		Time myLifeTime;
		Time myDeltaTime;

		bool myIsPaused;
	};

	inline Time CStopWatch::GetLifeTime() const
	{
		return myLifeTime;
	}

	inline Time CStopWatch::GetDeltaTime() const
	{
		return myDeltaTime;
	}
}
