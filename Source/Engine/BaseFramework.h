#pragma once

namespace wendy
{
	class CBaseWindow;

	class CBaseFramework
	{
	public:
		CBaseFramework() {}
		virtual ~CBaseFramework() {}

		virtual bool Init(CBaseWindow& aWindow) = 0;
		virtual bool BeginFrame() = 0;
		virtual bool EndFrame() = 0;
		virtual void OnWindowResize(const std::uint32_t aWidth, const std::uint32_t aHeight) = 0;
	};
}
