#include "stdafx.h"
#include "ThreadNamer.h"

static const std::string locUnNamedThread("UnNamed");

#ifdef _WIN32
#include <windows.h>
static std::map<uint32_t, std::string> locThreadNames;

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

namespace CU
{
	void SetThreadName(const uint32_t dwThreadID, const std::string& threadName);
	const std::string& GetThreadName(const uint32_t aThreadID);

	void SetThreadName(const std::string& threadName)
	{
#ifdef _WIN32
		DWORD threadId = GetCurrentThreadId();
		SetThreadName(threadId, threadName);
#endif // _WIN32
	}

	void SetThreadName(std::thread& thread, const std::string& threadName)
	{
#ifdef _WIN32
		DWORD threadId = ::GetThreadId(thread.native_handle());
		SetThreadName(threadId, threadName);
#endif // _WIN32
	}

	void SetThreadName(uint32_t dwThreadID, const std::string& threadName)
	{
#ifdef _WIN32
		locThreadNames[dwThreadID] = threadName;
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
	}

	const std::string& GetThreadName()
	{
#ifdef _WIN32
		DWORD id = GetCurrentThreadId();
		return GetThreadName(id);
#endif // _WIN32
	}

	const std::string& GetThreadName(std::thread& aThread)
	{
#ifdef _WIN32
		DWORD id = ::GetThreadId(aThread.native_handle());
		return GetThreadName(id);
#endif // _WIN32
	}

	const std::string& GetThreadName(const uint32_t aThreadID)
	{
#ifdef _WIN32
		if (locThreadNames.find(aThreadID) != locThreadNames.end())
		{
			return locThreadNames[aThreadID];
		}

		return locUnNamedThread;
#endif // _WIN32
	}
}
