#pragma once

class CStateStack;

class CBaseState
{
public:
	CBaseState(CStateStack& aStateStack);
	virtual ~CBaseState();

	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual void Render() = 0;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual bool LetThroughUpdate() = 0;
	virtual bool LetThroughRender() = 0;

	void SetShouldContinue(const bool aShouldContinue);

private:
	CStateStack& myStateStack;

protected:
	bool myShouldContinue;
};
