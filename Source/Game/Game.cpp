#include "stdafx.h"
#include "Game.h"

#include "StateStack.h"
#include "InitState.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

bool CGame::Init()
{
	myStateStack = std::make_unique<CStateStack>();
	if (!myStateStack)
	{
		return false;
	}

	std::unique_ptr<CInitState> initState = std::make_unique<CInitState>(*myStateStack);
	bool initSuccess = myStateStack->Push(std::move(initState));

	return initSuccess;
}

bool CGame::Update()
{
	bool updateSuccess = myStateStack->Update();
	return updateSuccess;
}

void CGame::Render()
{
	myStateStack->Render();
}
