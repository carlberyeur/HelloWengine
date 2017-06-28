#pragma once

namespace wendy
{
	class CBaseRenderer;
	class COpenGLRenderer;

	class IRenderCommand
	{
	public:
		IRenderCommand() {}
		virtual ~IRenderCommand() {}

		virtual void Execute(CBaseRenderer& /*aRenderer*/) {}
		virtual void Execute(COpenGLRenderer& aRenderer) = 0;
	};
}
