#include "stdafx.h"
#include "BaseState.h"

CBaseState::CBaseState(CStateStack& aStateStack)
	: myStateStack(aStateStack)
	, myShouldContinue(true)
{
}

CBaseState::~CBaseState()
{
}

void CBaseState::SetShouldContinue(const bool aShouldContinue)
{
	myShouldContinue = aShouldContinue;
}
