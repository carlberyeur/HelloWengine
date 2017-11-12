#include "stdafx.h"
#include "ChangeEffectCommand.h"

#include "OpenGLRenderer.h"
#include "GLEffect.h"

namespace pulp
{
	CChangeEffectCommand::CChangeEffectCommand(const EffectID aEffect)
		: myEffect(aEffect)
	{
	}

	CChangeEffectCommand::~CChangeEffectCommand()
	{
	}

	void pulp::CChangeEffectCommand::Execute(COpenGLRenderer& aRenderer)
	{
		CGLEffect* effect = aRenderer.GetEffect(myEffect);
		if (!effect) return;

		effect->Activate();
	}
}
