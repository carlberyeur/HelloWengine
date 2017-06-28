#pragma once

namespace cu
{
	class CWork;
}

using Work = cu::CWork;

namespace WorkPool
{
	bool Init(const bool aSingleThreaded = false);
	void ProcessSingleThreaded();
	void Shutdown();
	void AddWork(Work&& aWork);
};
