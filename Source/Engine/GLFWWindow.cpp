#include "stdafx.h"
#include "GLFWWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#if defined(_WIN32)

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3native.h>
#define GET_NATIVE_WINDOW_PTR() glfwGetWin32Window(myWindow)

#elif defined(_LINUX)

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW\glfw3native.h>
#define GET_NATIVE_WINDOW_PTR() glfwGetX11Display(myWindow)

#elif defined(__APPLE__)

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>
#define GET_NATIVE_WINDOW_PTR() glfwGetCocoaWindow(myWindow)

#else

#error "Don't do this to me"

#endif // _WIN32


namespace wendy
{
	CGLFWWindow::CGLFWWindow()
		: myWindow(nullptr)
	{
	}

	CGLFWWindow::~CGLFWWindow()
	{
		if (myWindow)
		{
			glfwDestroyWindow(myWindow);
			glfwTerminate();
		}
	}

	bool CGLFWWindow::Init(const std::uint32_t aWidth, const std::uint32_t aHeight, const std::string& aTitle)
	{
		if (!glfwInit())
		{
			return false;
		}

		myWindow = glfwCreateWindow(static_cast<int>(aWidth), static_cast<int>(aHeight), aTitle.c_str(), nullptr, nullptr);
		if (!myWindow)
		{
			return false;
		}
		//glfwGetProcAddress()
		MakeContextCurrent();
		glfwSetWindowUserPointer(myWindow, this);

		return true;
	}

	bool CGLFWWindow::PollEvents()
	{
		glfwPollEvents();
		return true;
	}

	void* CGLFWWindow::GetNativeHandle()
	{
		return GET_NATIVE_WINDOW_PTR();
	}

	bool CGLFWWindow::IsOpen()
	{
		return !glfwWindowShouldClose(myWindow);
	}

	void CGLFWWindow::MakeContextCurrent()
	{
		glfwMakeContextCurrent(myWindow);
	}

	void CGLFWWindow::MakeContextCurrent(std::nullptr_t)
	{
		glfwMakeContextCurrent(nullptr);
	}

	bool CGLFWWindow::AssignSwapBuffersFunction(cu::CFunction<void>& aSwapBufferFunctionPointer)
	{
		aSwapBufferFunctionPointer = [this]()
		{
			glfwSwapBuffers(myWindow);
		};
		return true;
	}

	bool CGLFWWindow::GetExtensionLoaderFunction(cu::CFunction<void(*)(), const std::string&>& aLoadExtensionFunction)
	{
		aLoadExtensionFunction = [](const std::string& aProcedureName) -> void(*)() { return glfwGetProcAddress(aProcedureName.c_str()); };
		return true;
	}

	void CGLFWWindow::KeyCallback(int aKey, int /*aScanCode*/, int aAction, int /*aModifierKeyBits*/)
	{
		if (myKeyboardCallback)
		{
			myKeyboardCallback(aKey, aAction);
		}
	}

	void CGLFWWindow::MousePositionCallback(double /*aX*/, double /*aY*/)
	{
		if (myKeyboardCallback)
		{
			//myKeyboardCallback(aKey, aAction);
		}
	}

	void CGLFWWindow::MouseButtonCallback(int /*aButton*/, int /*aAction*/, int /*aModifierMouseBits*/)
	{
		if (myKeyboardCallback)
		{
			//myKeyboardCallback(aKey, aAction);
		}
	}

	void CGLFWWindow::FileDroppedCallback(int /*aFileCount*/, const char** /*aFileNames*/)
	{
		if (myKeyboardCallback)
		{
			//myKeyboardCallback(aKey, aAction);
		}
	}

	void CGLFWWindow::KeyCallback(GLFWwindow* aWindow, int aKey, int aScanCode, int aAction, int aModifierKeys)
	{
		void* userPointer = glfwGetWindowUserPointer(aWindow);
		if (userPointer)
		{
			CGLFWWindow* window = static_cast<CGLFWWindow*>(userPointer);
			window->KeyCallback(aKey, aScanCode, aAction, aModifierKeys);
		}
	}

	void CGLFWWindow::MousePositionCallback(GLFWwindow* aWindow, double aX, double aY)
	{
		void* userPointer = glfwGetWindowUserPointer(aWindow);
		if (userPointer)
		{
			CGLFWWindow* window = static_cast<CGLFWWindow*>(userPointer);
			window->MousePositionCallback(aX, aY);
		}
	}

	void CGLFWWindow::MouseButtonCallback(GLFWwindow* aWindow, int aButton, int aAction, int aModifierKeyBits)
	{
		void* userPointer = glfwGetWindowUserPointer(aWindow);
		if (userPointer)
		{
			CGLFWWindow* window = static_cast<CGLFWWindow*>(userPointer);
			window->MouseButtonCallback(aButton, aAction, aModifierKeyBits);
		}
	}

	void CGLFWWindow::FileDroppedCallback(GLFWwindow* aWindow, int aFileCount, const char** aFileNames)
	{
		void* userPointer = glfwGetWindowUserPointer(aWindow);
		if (userPointer)
		{
			CGLFWWindow* window = static_cast<CGLFWWindow*>(userPointer);
			window->FileDroppedCallback(aFileCount, aFileNames);
		}
	}
}
