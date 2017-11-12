#pragma once

namespace pulp
{
	class CBaseWindow
	{
	public:
		CBaseWindow();
		virtual ~CBaseWindow();

		virtual bool Init(const cu::Vector2ui& aWindowSize, const std::string& aTitle) = 0;
		virtual bool PollEvents() = 0;
		virtual bool IsOpen() = 0;
		virtual void* GetNativeHandle() = 0;

		virtual void MakeContextCurrent() {}
		virtual void MakeContextCurrent(std::nullptr_t) {}
		virtual bool AssignSwapBuffersFunction(cu::CFunction<void>& aSwapBufferFunctionPointer);
		virtual bool GetExtensionLoaderFunction(cu::CFunction<void(*)(), const std::string&>& aLoadExtensionFunction);

		virtual cu::Vector2ui GetWindowSize() const = 0;
		virtual cu::Vector2f GetWindowSizeF() const = 0;

		void SetKeyboardCallback(const cu::CFunction<void, int, int>& aKeyboardCallback);

	protected:
		cu::CFunction<void, int, int> myKeyboardCallback;
	};
}
