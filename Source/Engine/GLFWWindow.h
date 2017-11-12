#pragma once
#include "BaseWindow.h"

struct GLFWwindow;

namespace pulp
{

	class CGLFWWindow : public CBaseWindow
	{
	public:
		CGLFWWindow();
		~CGLFWWindow();

		virtual bool Init(const cu::Vector2ui& aWindowSize, const std::string& aTitle) override;
		virtual bool PollEvents() override;
		virtual void* GetNativeHandle() override;
		virtual bool IsOpen() override;

		virtual void MakeContextCurrent() override;
		virtual void MakeContextCurrent(std::nullptr_t) override;
		virtual bool AssignSwapBuffersFunction(cu::CFunction<void>& aSwapBufferFunctionPointer) override;
		virtual bool GetExtensionLoaderFunction(cu::CFunction<void(*)(), const std::string&>& aLoadExtensionFunction) override;

		virtual cu::Vector2ui GetWindowSize() const override;
		virtual cu::Vector2f GetWindowSizeF() const override;

	private:
		void KeyCallback(int aKey, int aScanCode, int aAction, int aModifierKeyBits);
		void MousePositionCallback(double aX, double aY);
		void MouseButtonCallback(int aButton, int aAction, int aModifierKeyBits);
		void FileDroppedCallback(int aFileCount, const char** aFileNames);

		static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int aAction, int aModifierKeys);
		static void MousePositionCallback(GLFWwindow* aWindow, double aX, double aY);
		static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int aAction, int aModifierKeyBits);
		static void FileDroppedCallback(GLFWwindow* aWindow, int aFileCount, const char** aFileNames);

		GLFWwindow* myWindow;
	};
}
