#include "stdafx.h"
#include "SetCullModeCommand.h"
#include "OpenGLFramework.h"

namespace wendy
{
	CSetCullModeCommand::CSetCullModeCommand(const std::uint_fast8_t aCullModeFlags)
		: myCullModeFlags(aCullModeFlags)
	{
		assert("Cannot set wireframe and fill" && !((myCullModeFlags & eCullMode_Fill) && (myCullModeFlags & eCullMode_WireFrame)));
		assert("Cannot set back- and frontface culling" && !((myCullModeFlags & eCullMode_Back) && (myCullModeFlags & eCullMode_Front)));
	}

	CSetCullModeCommand::~CSetCullModeCommand()
	{
	}

	void CSetCullModeCommand::Execute(COpenGLRenderer& /*aRenderer*/)
	{
		if (myCullModeFlags & eCullMode_Fill)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (myCullModeFlags & eCullMode_WireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (myCullModeFlags & eCullMode_Back)
		{
			glCullFace(GL_BACK);
		}
		else if (myCullModeFlags & eCullMode_Front)
		{
			glCullFace(GL_FRONT);
		}
	}
}