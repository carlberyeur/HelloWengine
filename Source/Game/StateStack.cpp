#include "stdafx.h"
#include "StateStack.h"
#include "BaseState.h"

CStateStack::CStateStack()
{
}

CStateStack::~CStateStack()
{
}

bool CStateStack::Update()
{
	int last = myStates.Size<int>() - 1;

	bool shouldContinue = UpdateAtIndex(last);
	if (!shouldContinue)
	{
		Pop();
	}

	return !myStates.empty();
}

void CStateStack::Render()
{
	int last = myStates.Size<int>() - 1;
	RenderAtIndex(last);
}

bool CStateStack::Push(std::unique_ptr<CBaseState> aState)
{
	if (aState->Init())
	{
		if (!myStates.empty())
		{
			myStates.back()->OnExit();
		}

		myStates.push_back(std::move(aState));
		myStates.back()->OnEnter();
		return true;
	}

	return false;
}

void CStateStack::Pop()
{
	if (!myStates.empty())
	{
		myStates.back()->OnExit();
	}

	myStates.pop_back();
	
	if (!myStates.empty())
	{
		myStates.back()->OnEnter();
	}
}

bool CStateStack::UpdateAtIndex(const int aIndex)
{
	if (aIndex < 0)
	{
		return true;
	}

	if (myStates.At(aIndex)->LetThroughUpdate())
	{
		UpdateAtIndex(aIndex - 1);
	}

	bool shouldContinue = myStates.At(aIndex)->Update();
	return shouldContinue;
}

void CStateStack::RenderAtIndex(const int aIndex)
{
	if (aIndex < 0)
	{
		return;
	}

	if (myStates.At(aIndex)->LetThroughRender())
	{
		RenderAtIndex(aIndex - 1);
	}

	myStates.At(aIndex)->Render();
}
