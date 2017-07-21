#include "stdafx.h"
#include "DebugLogger.h"

#include <iostream>
#ifdef _WIN32
#include <Windows.h>

extern "C"
{
	_CRTIMP void __cdecl _wassert(
		_In_z_ wchar_t const* _Message,
		_In_z_ wchar_t const* _File,
		_In_   unsigned       _Line
	);
}
#elif defined(__APPLE__)
#include <CoreFoundation/CFUserNotification.h>

#endif


#define SUPRESS_UNUSED_WARNING(variable) variable
constexpr unsigned int MAX_STRING_BUFFER_SIZE = 2048u;

#if defined _WIN32
	#define VSPRINTF vsprintf_s
	#define WVSPRINTF wvsprintf
	#define DebugOutputWindow8 OutputDebugStringA
	#define DebugOutputWindow16 OutputDebugStringW
#else
	#define VSPRINTF vsprintf
	#define WVSPRINTF(B, FS, ARGS) 
//vsprintf((B), cast this badboy to char(FS), (ARGS))
	#define DebugOutputWindow8 (void)
	#define DebugOutputWindow16 (void)
#endif

namespace cu
{
	CDebugLogger* CDebugLogger::theInstance = nullptr;

	void CDebugLogger::CreateInstance()
	{
		assert(theInstance == nullptr);
		theInstance = new CDebugLogger();
	}
	
	void CDebugLogger::DestroyInstance()
	{
		assert(theInstance != nullptr);
		delete theInstance;
		theInstance = nullptr;
	}
	
	CDebugLogger* CDebugLogger::GetInstance()
	{
		return theInstance;
	}

	void CDebugLogger::PrintMessage(const char* aFormattedString, ...)
	{
		char buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aFormattedString);
		VSPRINTF(buffer, aFormattedString, args);
		va_end(args);

		std::cout << buffer << std::endl;
		DebugOutputWindow8(buffer);
	}

	void CDebugLogger::PrintMessage(const wchar_t* aFormattedString, ...)
	{
		wchar_t buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aFormattedString);
		WVSPRINTF(buffer, aFormattedString, args);
		va_end(args);

		std::wcout << buffer << std::endl;
		DebugOutputWindow16(buffer);
	}

	void CDebugLogger::ShowMessageBox(const char* aFormattedString, ...)
	{
		char buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aFormattedString);
		VSPRINTF(buffer, aFormattedString, args);
		va_end(args);
		
		eMessageBoxReturn result;
		
#ifdef _WIN32
		result = ShowMessageBoxWin(buffer);
#elif defined(__APPLE__)
		result = ShowMessageBoxMacOS(buffer);
#endif
		
		switch(result)
		{
			case eMessageBoxReturn::eIgnore:
				break;
			case eMessageBoxReturn::eAbort:
				std::cout << buffer << std::endl;
				DebugOutputWindow8(buffer);
				exit(1337);
				break;
			case eMessageBoxReturn::eRetry:
				//_wassert(nullptr, nullptr, 0);
			break;
		}
	}

	void CDebugLogger::ShowMessageBox(const wchar_t* aFormattedString, ...)
	{
#ifdef _WIN32
		wchar_t buffer[MAX_STRING_BUFFER_SIZE] = {};
		va_list args;

		va_start(args, aFormattedString);
		wvsprintf(buffer, aFormattedString, args);
		va_end(args);

		int error = MessageBoxW(nullptr, buffer, L"Error", MB_ABORTRETRYIGNORE);
		switch (error)
		{
		case IDIGNORE:
			break;
		case IDABORT:
			std::wcout << buffer << std::endl;
			DebugOutputWindow16(buffer);
			exit(1337);
			break;
		case IDRETRY:
			_wassert(nullptr, nullptr, 0);
			break;
		}
#elif defined(__APPLE__)
		DL_PRINT("ShowMessageBox not implemented on macOS", false);
	#pragma message("ShowMessageBox not implemented on macOS")
#else

#error "Fix this! ...or just go with supressing the warning"

#endif
	}
	
	CDebugLogger::eMessageBoxReturn CDebugLogger::ShowMessageBoxMacOS(const char* aString)
	{
#ifdef __APPLE__
		const int IDIGNORE 	 =	1;
		const int IDABORT	 =	0;
		const int IDRETRY	 =	2;

		//convert the strings from char* to CFStringRef
		CFStringRef header_ref = CFStringCreateWithCString( NULL, "Error", kCFStringEncodingUTF8);
		CFStringRef message_ref = CFStringCreateWithCString( NULL, aString, kCFStringEncodingUTF8);
			
		CFOptionFlags result;  //result code from the message box
			
		//launch the message box
		CFUserNotificationDisplayAlert(
			0, // no timeout
			kCFUserNotificationNoteAlertLevel, //change it depending message_type flags ( MB_ICONASTERISK.... etc.)
			NULL, //icon url, use default, you can change it depending message_type flags
			NULL, //not used
			NULL, //localization of strings
			header_ref, //header text
			message_ref, //message text
			CFSTR("Abort"), //default button
			CFSTR("Ignore"), //alternate button title
			CFSTR("Retry"), //other button title, null--> no other button
			&result //response flags
			);
		
		//Clean up the strings
		CFRelease( header_ref );
		CFRelease( message_ref );
			
		//Convert the result
		
		switch (result)
		{
			case IDIGNORE:
				return eMessageBoxReturn::eIgnore;
			case IDABORT:
				return eMessageBoxReturn::eAbort;
			case IDRETRY:
				return eMessageBoxReturn::eRetry;
			default:
				return eMessageBoxReturn::eAbort;
		break;
		}
#endif
		
		return eMessageBoxReturn::eAbort;
	}
	
	CDebugLogger::eMessageBoxReturn CDebugLogger::ShowMessageBoxWin(const char* aString)
	{
#ifdef _WIN32
		int error = MessageBoxA(nullptr, aString, "Error", MB_ABORTRETRYIGNORE);
		switch (error)
		{
			case IDIGNORE:
				return eMessageBoxReturn::eIgnore;
			case IDABORT:
				return eMessageBoxReturn::eAbort;
			case IDRETRY:
				return eMessageBoxReturn::eRetry;
			default:
				return eMessageBoxReturn::eAbort;
				
		}
#endif
		return eMessageBoxReturn::eAbort;
	}

	void CDebugLogger::SetConsoleColor(const unsigned short aColor)
	{
#ifdef _WIN32
		HANDLE hConsole = nullptr;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				
		if (hConsole != nullptr)
		{
			SetConsoleTextAttribute(hConsole, aColor);
		}
#elif defined(__APPLE__)
		DL_PRINT("SetConsoleColor not implemented on macOS", false);
	#pragma message("SetConsoleColor not implemented on macOS")
#else
#error "Fix this! ...or just go with supressing the warning"
		SUPRESS_UNUSED_WARNING(aColor);
#endif
	}

	CDebugLogger::CDebugLogger()
	{
	}

	CDebugLogger::~CDebugLogger()
	{
	}
}
