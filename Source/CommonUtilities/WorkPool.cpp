#include "stdafx.h"
#include "WorkPool.h"
#include "Work.h"

#include "ThreadNamer.h"

#include <condition_variable>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


namespace WorkPool
{
	using Worker = std::thread;

	static std::vector<Worker> locWorkers;
	static std::queue<Work> locWorks;

	static size_t locThreadCount = 0u;

	static std::mutex locQueueMutex;
	static std::condition_variable locConditionalVariable;
	static std::atomic_bool locIsStopped(true);

	void Process(const size_t aID);
	bool CanEnter();

	bool Init(const bool aSingleThreaded)
	{
		unsigned int hardwareConcurrency = std::thread::hardware_concurrency();
		locThreadCount = (aSingleThreaded || hardwareConcurrency == 0u) ? 1u : hardwareConcurrency - 1u;
		locWorkers.reserve(locThreadCount);

		for (size_t i = 0; i < locThreadCount; ++i)
		{
			locWorkers.push_back(Worker(&Process, i));
		}

		locIsStopped = false;

		return locWorkers.size() > 0;
	}

	void Shutdown()
	{
		std::unique_lock<std::mutex> backDoor(locQueueMutex);
		locIsStopped = true;
		locConditionalVariable.notify_all();
		backDoor.unlock();

		for (Worker& worker : locWorkers)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}

		locWorkers.clear();
	}

	void AddWork(Work&& aWork)
	{
		std::unique_lock<std::mutex> backDoor(locQueueMutex);
		locWorks.push(std::move(aWork));
		locConditionalVariable.notify_one();
	}

	void Process(const size_t aID)
	{
#ifdef _WIN32
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
#elif defined __linux__
		//http ://stackoverflow.com/questions/10876342/equivalent-of-setthreadpriority-on-linux-pthreads
#endif

		while (locIsStopped)
		{
			std::this_thread::yield();
		}

		const std::string idleName = "Worker " + std::to_string(aID + 1);
		CU::SetThreadName(idleName);
		std::unique_lock<std::mutex> backDoor(locQueueMutex, std::defer_lock);

		while (true)
		{
			backDoor.lock();

			locConditionalVariable.wait(backDoor, CanEnter);

			if (locIsStopped)
			{
				break;
			}

			Work work = std::move(locWorks.front());
			locWorks.pop();

			backDoor.unlock();

			bool changeName = !work.GetName().empty();
			if (changeName)
			{
				CU::SetThreadName(work.GetName());
			}

			work.DoWork();

			if (changeName)
			{
				CU::SetThreadName(idleName);
			}

			if (!work.IsComplete() && !locIsStopped)
			{
				AddWork(std::move(work));
			}

			std::this_thread::yield();
		}
	}

	void ProcessSingleThreaded()
	{
		const std::string idleName = "Single Worker";

		while (!locIsStopped)
		{
			Work work = std::move(locWorks.front());
			locWorks.pop();

			bool changeName = !work.GetName().empty();
			if (changeName)
			{
				CU::SetThreadName(work.GetName());
			}

			work.DoWork();

			if (changeName)
			{
				CU::SetThreadName(idleName);
			}

			if (!work.IsComplete() && !locIsStopped)
			{
				AddWork(std::move(work));
			}

			std::this_thread::yield();
		}
	}

	bool CanEnter()
	{
		return locIsStopped || !locWorks.empty();
	}
}
