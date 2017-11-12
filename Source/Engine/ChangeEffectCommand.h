#pragma once
#include "RenderCommand.h"

namespace wendy
{
	typedef struct EffectID_t* EffectID;

	class CChangeEffectCommand : public IRenderCommand
	{
	public:
		CChangeEffectCommand(const EffectID aEffect);
		~CChangeEffectCommand();

		virtual void Execute(COpenGLRenderer& aRenderer) override;

	private:
		const EffectID myEffect;
	};
}
