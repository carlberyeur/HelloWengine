#pragma once

#define SET_RED() cu::CDebugLogger::SetConsoleColor(CONSOLE_TEXT_COLOR_RED)
#define SET_YELLOW() cu::CDebugLogger::SetConsoleColor(CONSOLE_TEXT_COLOR_YELLOW)
#define SET_GREEN() cu::CDebugLogger::SetConsoleColor(CONSOLE_TEXT_COLOR_GREEN)
#define SET_WHITE() cu::CDebugLogger::SetConsoleColor(CONSOLE_TEXT_COLOR_WHITE)

#ifndef _RETAIL

#define DL_PRINT(msg, ...) cu::CDebugLogger::PrintMessage(msg, __VA_ARGS__)
#define DL_PRINT_WARNING(msg, ...) do { SET_YELLOW(); cu::CDebugLogger::PrintMessage(msg, __VA_ARGS__); SET_WHITE(); } while(false)
#define DL_PRINT_ERROR(msg, ...) do { SET_RED(); cu::CDebugLogger::PrintMessage(msg, __VA_ARGS__); SET_WHITE(); } while(false)
#define DL_PRINT_INFO(msg, ...) do { SET_GREEN(); cu::CDebugLogger::PrintMessage(msg, __VA_ARGS__); SET_WHITE(); } while(false)

#define DL_MESSAGE_BOX(msg, ...) cu::CDebugLogger::ShowMessageBox(msg, __VA_ARGS__)

#else // !_RETAIL

#define DL_PRINT(msg, ...) (msg)
#define DL_PRINT_WARNING(msg, ...) (msg)
#define DL_PRINT_ERROR(msg, ...) (msg)
#define DL_PRINT_INFO(msg, ...) (msg)

#define DL_MESSAGE_BOX(msg, ...) (msg)

#endif // !_RETAIL

namespace cu
{
	const unsigned short CONSOLE_TEXT_COLOR_RED = 12;
	const unsigned short CONSOLE_TEXT_COLOR_YELLOW = 14;
	const unsigned short CONSOLE_TEXT_COLOR_GREEN = 10;
	const unsigned short CONSOLE_TEXT_COLOR_WHITE = 15;

	class CDebugLogger
	{
	public:
		static void CreateInstance();
		static void DestroyInstance();
		static CDebugLogger* GetInstance();

		static void PrintMessage(const char* aFormattedString, ...);
		static void PrintMessage(const wchar_t* aFormattedString, ...);

		static void ShowMessageBox(const char* aFormattedString, ...);
		static void ShowMessageBox(const wchar_t* aFormattedString, ...);

		static void SetConsoleColor(const unsigned short aColor);

	private:
		CDebugLogger();
		~CDebugLogger();

		static CDebugLogger* theInstance;
	};
}

#undef SET_RED
#undef SET_YELLOW
#undef SET_GREEN
#undef SET_WHITE
