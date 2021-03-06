#pragma once
#include "RenderCommand.h"

namespace wendy
{
	enum class eBlendState
	{
		eNoBlend,
		eAlphaBlend
	};

	class CSetBlendStateCommand : public IRenderCommand
	{
	public:
		CSetBlendStateCommand(const eBlendState aBlendState);
		~CSetBlendStateCommand();

		virtual void Execute(COpenGLRenderer& aRenderer) override;

	private:
		const eBlendState myBlendState;
	};
}
