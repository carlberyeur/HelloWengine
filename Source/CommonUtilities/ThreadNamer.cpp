#include "stdafx.h"
#include "ThreadNamer.h"

static const std::string locUnNamedThread("UnNamed");
static std::map<uint32_t, std::string> locThreadNames;

static std::mutex locThreadNameMutex;

#ifdef _WIN32
#include <windows.h>

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)
#endif // _WIN32

#ifdef __APPLE__
#include <pthread.h>
#endif

namespace CU
{
	void SetThreadName(const uint32_t dwThreadID, const std::string& threadName);
	const std::string& GetThreadName(const uint32_t aThreadID);
	void SaveThreadName(uint32_t dwThreadID, const std::string& threadName);

	void SetThreadName(const std::string& threadName)
	{
#ifdef _WIN32
		DWORD threadId = GetCurrentThreadId();
		SetThreadName(threadId, threadName);
#elif defined(__APPLE__)
		pthread_setname_np(threadName.c_str());
		
		uint64_t threadId;
		pthread_threadid_np(NULL, &threadId);
		
		SetThreadName(static_cast<uint32_t>(threadId), threadName);

#endif // _WIN32
	}

	void SetThreadName(std::thread& thread, const std::string& threadName)
	{
#ifdef _WIN32
		DWORD threadId = ::GetThreadId(thread.native_handle());
		SetThreadName(threadId, threadName);
#elif defined(__APPLE__)
		DL_PRINT("Mac OS X: must be set from within the thread (can't specify thread ID)", false);
	#pragma message("Mac OS X: must be set from within the thread (can't specify thread ID)")
#endif // _WIN32
	}

	void SetThreadName(uint32_t dwThreadID, const std::string& threadName)
	{
#ifdef _WIN32
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName.c_str();
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;

		__try
		{
			const DWORD MS_VC_EXCEPTION = 0x406D1388;
			RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
		}
#endif // _WIN32
		
		SaveThreadName(dwThreadID, threadName);
	}

	const std::string& GetThreadName()
	{
		uint32_t id = 0;
		
#ifdef _WIN32
		id = static_cast<uint32_t>(GetCurrentThreadId());
#elif defined(__APPLE__)
		uint64_t threadId;
		pthread_threadid_np(NULL, &threadId);
		
		id = static_cast<uint32_t>(threadId);
#endif
		return GetThreadName(id);
	}

	const std::string& GetThreadName(std::thread& aThread)
	{
		uint32_t id = 0;
#ifdef _WIN32
		id = static_cast<uint32_t>(::GetThreadId(aThread.native_handle()));
		
#elif defined(__APPLE__)
		uint64_t threadId;
		pthread_threadid_np(aThread.native_handle(), &threadId);
		
		id = static_cast<uint32_t>(threadId);
#endif
		
		return GetThreadName(id);

	}

	const std::string& GetThreadName(const uint32_t aThreadID)
	{
		std::lock_guard<std::mutex> lock(locThreadNameMutex);

		if (locThreadNames.find(aThreadID) != locThreadNames.end())
		{
			return locThreadNames[aThreadID];
		}

		return locUnNamedThread;
	}

	void SaveThreadName(uint32_t dwThreadID, const std::string& threadName)
	{
		std::lock_guard<std::mutex> lock(locThreadNameMutex);
		locThreadNames[dwThreadID] = threadName;
	}
}
