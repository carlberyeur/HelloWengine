#pragma once
#include "RenderCommand.h"

namespace wendy
{
	enum eCullMode : std::uint_fast8_t
	{
		eCullMode_Back = 1 << 0,
		eCullMode_Front = 1 << 1,
		eCullMode_Fill = 1 << 2,
		eCullMode_WireFrame = 1 << 3
	};

	class CSetCullModeCommand : public IRenderCommand
	{
	public:
		CSetCullModeCommand(const std::uint_fast8_t aCullModeFlags);
		~CSetCullModeCommand();

		virtual void Execute(COpenGLRenderer& aRenderer) override;

	private:
		const std::uint_fast8_t myCullModeFlags;
	};
}
