#pragma once
#include "BaseState.h"

#include "../CommonUtilities/StopWatch.h"

namespace wendy
{
	class CScene;
}

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

private:
	std::unique_ptr<wendy::CScene> myScene;

	//size_t myTorus;
	size_t myTorus;
	size_t myTumbleWeed;

	cu::CStopWatch myStopWatch;
	float myAngle;
};
