#include "stdafx.h"
#include "SetBlendStateCommand.h"
#include "OpenGLFramework.h"

namespace wendy
{
	CSetBlendStateCommand::CSetBlendStateCommand(const eBlendState aBlendState)
		: myBlendState(aBlendState)
	{
	}

	CSetBlendStateCommand::~CSetBlendStateCommand()
	{
	}

	void CSetBlendStateCommand::Execute(COpenGLRenderer& /*aRenderer*/)
	{
		switch (myBlendState)
		{
		case eBlendState::eNoBlend:
			glBlendFunc(GL_ONE, GL_ZERO);
			break;
		case eBlendState::eAlphaBlend:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		}
	}
}
