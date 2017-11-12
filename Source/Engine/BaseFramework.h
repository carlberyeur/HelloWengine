#pragma once

namespace pulp
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
		virtual void OnWindowResize(const cu::Vector2ui& aWindowSize) = 0;
	};
}
