#pragma once
#include "RenderCommand.h"

namespace pulp
{
	typedef struct ConstantBufferID_t* ConstantBufferID;

	class CSetTextureSlotCommand : public IRenderCommand
	{
	public:
		CSetTextureSlotCommand(const ConstantBufferID aTextureSlot, const int aSlotValue);
		~CSetTextureSlotCommand();

		virtual void Execute(COpenGLRenderer& aRenderer) override;

	private:
		const ConstantBufferID myTextureSlot;
		const int mySlotValue;
	};
}
