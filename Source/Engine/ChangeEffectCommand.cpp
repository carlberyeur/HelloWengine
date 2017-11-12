#include "stdafx.h"
#include "ChangeEffectCommand.h"

#include "OpenGLRenderer.h"
#include "GLEffect.h"

namespace wendy
{
	CChangeEffectCommand::CChangeEffectCommand(const EffectID aEffect)
		: myEffect(aEffect)
	{
	}

	CChangeEffectCommand::~CChangeEffectCommand()
	{
	}

	void wendy::CChangeEffectCommand::Execute(COpenGLRenderer& aRenderer)
	{
		CGLEffect* effect = aRenderer.GetEffect(myEffect);
		if (!effect) return;

		effect->Activate();
	}
}
