#pragma once
#include "BaseState.h"

class CInitState : public CBaseState
{
public:
	CInitState(CStateStack& aStateStack);
	~CInitState();

	virtual bool Init() override;

	virtual bool Update() override;
	virtual void Render() override;

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual bool LetThroughUpdate() override;
	virtual bool LetThroughRender() override;
};
