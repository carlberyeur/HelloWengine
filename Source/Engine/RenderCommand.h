#pragma once

namespace pulp
{
	class CBaseRenderer;
	class COpenGLRenderer;

	class IRenderCommand
	{
	public:
		IRenderCommand() {}
		virtual ~IRenderCommand() {}

		virtual void Execute(COpenGLRenderer& aRenderer) = 0;
	};
}
