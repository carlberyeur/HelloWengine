#include "stdafx.h"
#include "InitState.h"


CInitState::CInitState(CStateStack& aStateStack)
	: CBaseState(aStateStack)
{
}

CInitState::~CInitState()
{
}

bool CInitState::Init()
{
	return true;
}

bool CInitState::Update()
{
	return myShouldContinue;
}

void CInitState::Render()
{
}

void CInitState::OnEnter()
{
}

void CInitState::OnExit()
{
}

bool CInitState::LetThroughUpdate()
{
	return false;
}

bool CInitState::LetThroughRender()
{
	return false;
}
