#include "stdafx.h"
#include "SetTextureSlotCommand.h"

#include "OpenGLRenderer.h"
#include "GLUniformBuffer.h"

namespace pulp
{
	CSetTextureSlotCommand::CSetTextureSlotCommand(const ConstantBufferID aTextureSlot, const int aSlotValue)
		: myTextureSlot(aTextureSlot)
		, mySlotValue(aSlotValue)
	{
	}

	CSetTextureSlotCommand::~CSetTextureSlotCommand()
	{
	}

	void CSetTextureSlotCommand::Execute(COpenGLRenderer& aRenderer)
	{
		CGLUniformBuffer* textureSlot = aRenderer.GetUniformBuffer(myTextureSlot);
		if (!textureSlot) return;

		textureSlot->SetData(mySlotValue);
	}
}
