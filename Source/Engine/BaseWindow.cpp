#include "stdafx.h"
#include "BaseWindow.h"

namespace wendy
{
	CBaseWindow::CBaseWindow()
	{
	}

	CBaseWindow::~CBaseWindow()
	{
	}

	bool CBaseWindow::AssignSwapBuffersFunction(cu::CFunction<void>& /*aSwapBufferFunctionPointer*/)
	{
		return false;
	}

	bool CBaseWindow::GetExtensionLoaderFunction(cu::CFunction<void(*)(), const std::string&>& /*aLoadExtensionFunction*/)
	{
		return false;
	}

	void CBaseWindow::SetKeyboardCallback(const cu::CFunction<void, int, int>& aKeyboardCallback)
	{
		myKeyboardCallback = aKeyboardCallback;
	}
}
